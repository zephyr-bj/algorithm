#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>
#include <linux/atomic.h>

#define RB_ORDER 2                 /* 4 pages */
#define RB_PAGES (1 << RB_ORDER)
#define RB_SIZE  (RB_PAGES * PAGE_SIZE)

struct mmap_rb {
    struct page   **pages;
    atomic64_t     write_pos;
    atomic64_t     read_pos;
    atomic_t       users;
};

// Allocation (page-based, mmap-safe)
static struct mmap_rb *rb_alloc(void)
{
    int i;
    struct mmap_rb *rb;

    rb = kzalloc(sizeof(*rb), GFP_KERNEL);
    if (!rb)
        return NULL;

    rb->pages = kcalloc(RB_PAGES, sizeof(struct page *), GFP_KERNEL);
    if (!rb->pages)
        goto err_rb;

    for (i = 0; i < RB_PAGES; i++) {
        // NOT necessarilly physically contiguous pages
        rb->pages[i] = alloc_page(GFP_KERNEL | __GFP_ZERO);
        if (!rb->pages[i])
            goto err_pages;
    }

    atomic64_set(&rb->write_pos, 0);
    atomic64_set(&rb->read_pos, 0);
    atomic_set(&rb->users, 0);

    return rb;

err_pages:
    while (--i >= 0)
        __free_page(rb->pages[i]);
    kfree(rb->pages);
err_rb:
    kfree(rb);
    return NULL;
}

// Lifetime management (VMA open/close)
// Userspace mapping controls lifetime.
static void rb_vma_open(struct vm_area_struct *vma)
{
    struct mmap_rb *rb = vma->vm_private_data;
    atomic_inc(&rb->users);
}

static void rb_vma_close(struct vm_area_struct *vma)
{
    struct mmap_rb *rb = vma->vm_private_data;
    atomic_dec(&rb->users);
}

static const struct vm_operations_struct rb_vm_ops = {
    .open  = rb_vma_open,
    .close = rb_vma_close,
};

// mmap() implementation with permissions
static int rb_mmap(struct file *file, struct vm_area_struct *vma)
{
    struct mmap_rb *rb = file->private_data;
    unsigned long size = vma->vm_end - vma->vm_start;
    unsigned long addr = vma->vm_start;
    int i;

    if (size != RB_SIZE)
        return -EINVAL;

    /* Permission: read-only from userspace */
    if (vma->vm_flags & VM_WRITE)
        return -EPERM;

    vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

    for (i = 0; i < RB_PAGES; i++) {
        // This does NOT require physical contiguity
        // Userspace sees a virtually contiguous buffer
        // remap_pfn_range requires physically continuous
        int ret = vm_insert_page(vma, addr, rb->pages[i]);
        if (ret)
            return ret;
        addr += PAGE_SIZE;
    }

    vma->vm_ops = &rb_vm_ops;
    vma->vm_private_data = rb;
    rb_vma_open(vma);

    return 0;
}

// Lockless spinning (kernel → user)
static void rb_write(struct mmap_rb *rb, const void *data, size_t len)
{
    u64 w = atomic64_read(&rb->write_pos);
    u64 r = atomic64_read(&rb->read_pos);

    if (w - r + len > RB_SIZE)
        return; /* drop */

    while (len--) {
        size_t off = w & (RB_SIZE - 1);
        size_t pg  = off >> PAGE_SHIFT;
        size_t in  = off & (PAGE_SIZE - 1);

        ((char *)page_address(rb->pages[pg]))[in] =
            *((char *)data++);

        w++;
    }

    /* Publish after data is visible */
    smp_store_release(&rb->write_pos.counter, w);
}

// Cleanup on file close
static int rb_release(struct inode *ino, struct file *f)
{
    struct mmap_rb *rb = f->private_data;
    int i;

    if (atomic_read(&rb->users))
        return 0;  /* mappings still exist */

    for (i = 0; i < RB_PAGES; i++)
        __free_page(rb->pages[i]);

    kfree(rb->pages);
    kfree(rb);
    return 0;
}

/** Userspace code below **/
// Shared layout (must match kernel)
/* shared with kernel */
/* Assume
 * | header (1 page) | data pages ... |
 */        
struct rb_hdr {
    uint64_t write_pos;   /* kernel writes */
    uint64_t read_pos;    /* user writes */
};

#define PAGE_SIZE 4096
#define RB_PAGES  4
#define RB_SIZE   (PAGE_SIZE * (1 + RB_PAGES))
#define RB_MASK   (RB_PAGES * PAGE_SIZE - 1)

// Userspace mmap + setup
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdatomic.h>

int main(void)
{
    int fd = open("/dev/my_rb", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    void *map = mmap(NULL, RB_SIZE,
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    struct rb_hdr *hdr = map;
    uint8_t *data = (uint8_t *)map + PAGE_SIZE;
// Lockless consumer loop (spin-based)
    uint64_t r = 0;

    for (;;) {
        /* acquire pairs with kernel store_release */
        uint64_t w = atomic_load_explicit(
            (_Atomic uint64_t *)&hdr->write_pos,
            memory_order_acquire);

        if (r == w) {
            /* buffer empty → spin */
            __asm__ __volatile__("pause");
            continue;
        }

        /* consume one byte (example) */
        uint64_t off = r & RB_MASK;
        uint8_t val = data[off];

        printf("got: %u\n", val);

        r++;

        /* publish progress */
        atomic_store_explicit(
            (_Atomic uint64_t *)&hdr->read_pos,
            r,
            memory_order_release);
    }
}


