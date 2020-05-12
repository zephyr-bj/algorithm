/* <include/linux/pci.h>
 * define pci_pool dma_pool
 * #define pci_pool_create(name, pdev, size, align, allocation) \
        dma_pool_create(name, &pdev->dev, size, align, allocation)
 * #define pci_pool_destroy(pool) dma_pool_destroy(pool)
 * #define pci_pool_alloc(pool, flags, handle) dma_pool_alloc(pool, flags, handle)
 * #define pci_pool_zalloc(pool, flags, handle) \
        dma_pool_zalloc(pool, flags, handle)
 * #define pci_pool_free(pool, vaddr, addr) dma_pool_free(pool, vaddr, addr)
 * /
 
 // dma_pool_create
 // dma_pool_alloc
 // dma_pool_destroy
 // dma_pool_free
 // so the blocks are allocated "page" by "page", not the memory page, but dma_page struct
 // the first 4 bytes of a block contains offset to the next block, blocks can be arbitrarily added and remove
 // page.offset shows the current block position, as long as "page->offset < pool->allocation", there are available block in this page
 
/*
 * Non-uniform memory access (NUMA) is a computer memory design used in multiprocessing, 
 * where the memory access time depends on the memory location relative to the processor. 
 * Under NUMA, a processor can access its own local memory faster than non-local memory (memory 
 * local to another processor or memory shared between processors). The benefits of NUMA are limited 
 * to particular workloads, notably on servers where the data is often associated strongly with certain tasks or users.[1] 
 * <include/linux/device.h>
 * #ifdef CONFIG_NUMA
 * static inline int dev_to_node(struct device *dev)
 * {
 *     return dev->numa_node;
 * }
 * Linux divides the system’s hardware resources into multiple software abstractions called “nodes”. 
 * Linux maps the nodes onto the physical cells of the hardware platform, abstracting away some of the details for some architectures. 
 * As with physical cells, software nodes may contain 0 or more CPUs, memory and/or IO buses. 
 * And, again, memory accesses to memory on “closer” nodes–nodes that map to closer cells–will generally experience faster access times 
 * and higher effective bandwidth than accesses to more remote cells.
 * 
 * void * kmalloc_node (size_t size, gfp_t flags, int node);
 * kmalloc for non-local nodes, used to allocate from a specific node if available. Equivalent to kmalloc in the non-NUMA single-node case. 
 */
 
<include/linux/types.h>
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
typedef u64 dma_addr_t;
#else
typedef u32 dma_addr_t;
#endif

 <mm/dmapool.c>
 struct dma_pool {       /* the pool */
    struct list_head page_list;
    spinlock_t lock;
    size_t size;
    struct device *dev;
    size_t allocation;
    size_t boundary;
    char name[32];
    struct list_head pools;
};

struct dma_page {       /* cacheable header for 'allocation' bytes */
    struct list_head page_list;
    void *vaddr;
    dma_addr_t dma;
    unsigned int in_use;
    unsigned int offset;
};

static DEFINE_MUTEX(pools_lock);
static DEFINE_MUTEX(pools_reg_lock);

**
 * dma_pool_create - Creates a pool of consistent memory blocks, for dma.
 * @name: name of pool, for diagnostics
 * @dev: device that will be doing the DMA
 * @size: size of the blocks in this pool.
 * @align: alignment requirement for blocks; must be a power of two
 * @boundary: returned blocks won't cross this power of two boundary
 * Context: !in_interrupt()
 *
 * Returns a dma allocation pool with the requested characteristics, or
 * null if one can't be created.  Given one of these pools, dma_pool_alloc()
 * may be used to allocate memory.  Such memory will all have "consistent"
 * DMA mappings, accessible by the device and its driver without using
 * cache flushing primitives.  The actual size of blocks allocated may be
 * larger than requested because of alignment.
 *
 * If @boundary is nonzero, objects returned from dma_pool_alloc() won't
 * cross that size boundary.  This is useful for devices which have
 * addressing restrictions on individual DMA transfers, such as not crossing
 * boundaries of 4KBytes.
 */
struct dma_pool *dma_pool_create(const char *name, struct device *dev,
                 size_t size, size_t align, size_t boundary)
{
    struct dma_pool *retval;
    size_t allocation;
    bool empty = false;

    if (align == 0)
        align = 1;
    else if (align & (align - 1))
        return NULL;

    if (size == 0)
        return NULL;
    else if (size < 4)
        size = 4;

    if ((size % align) != 0)
        size = ALIGN(size, align);
    allocation = max_t(size_t, size, PAGE_SIZE);

    if (!boundary)
        boundary = allocation;
    else if ((boundary < size) || (boundary & (boundary - 1)))
        return NULL;
    
    //kmalloc_node — allocate memory from a specific node 
    retval = kmalloc_node(sizeof(*retval), GFP_KERNEL, dev_to_node(dev));
    if (!retval)
        return retval;

    strlcpy(retval->name, name, sizeof(retval->name));

    retval->dev = dev;

    INIT_LIST_HEAD(&retval->page_list);
    spin_lock_init(&retval->lock);
    retval->size = size;
    retval->boundary = boundary;
    retval->allocation = allocation;
    INIT_LIST_HEAD(&retval->pools);

    /*
     * pools_lock ensures that the ->dma_pools list does not get corrupted.
     * pools_reg_lock ensures that there is not a race between
     * dma_pool_create() and dma_pool_destroy() or within dma_pool_create()
     * when the first invocation of dma_pool_create() failed on
     * device_create_file() and the second assumes that it has been done (I
     * know it is a short window).
     */
    mutex_lock(&pools_reg_lock);
    mutex_lock(&pools_lock);
    if (list_empty(&dev->dma_pools))
        empty = true;
    list_add(&retval->pools, &dev->dma_pools);
    mutex_unlock(&pools_lock);
    if (empty) {
        int err;

        err = device_create_file(dev, &dev_attr_pools);
        if (err) {
            mutex_lock(&pools_lock);
            list_del(&retval->pools);
            mutex_unlock(&pools_lock);
            mutex_unlock(&pools_reg_lock);
            kfree(retval);
            return NULL;
        }
    }
    mutex_unlock(&pools_reg_lock);
    return retval;
}
EXPORT_SYMBOL(dma_pool_create);

static void pool_initialise_page(struct dma_pool *pool, struct dma_page *page)
{
    unsigned int offset = 0;
    unsigned int next_boundary = pool->boundary;

    do {
        unsigned int next = offset + pool->size;
        if (unlikely((next + pool->size) >= next_boundary)) {
            next = next_boundary;
            next_boundary += pool->boundary;
        }
        *(int *)(page->vaddr + offset) = next;
        offset = next;
    } while (offset < pool->allocation);
}

static struct dma_page *pool_alloc_page(struct dma_pool *pool, gfp_t mem_flags)
{
    struct dma_page *page;

    page = kmalloc(sizeof(*page), mem_flags);
    if (!page) 
        return NULL;
    page->vaddr = dma_alloc_coherent(pool->dev, pool->allocation,
                     &page->dma, mem_flags);
    if (page->vaddr) {
        pool_initialise_page(pool, page);
        page->in_use = 0;
        page->offset = 0;
    } else {
        kfree(page);
        page = NULL;
    }
    return page;
}

/**
 * dma_pool_alloc - get a block of consistent memory
 * @pool: dma pool that will produce the block
 * @mem_flags: GFP_* bitmask
 * @handle: pointer to dma address of block
 *
 * This returns the kernel virtual address of a currently unused block,
 * and reports its dma address through the handle.
 * If such a memory block can't be allocated, %NULL is returned.
 */
void *dma_pool_alloc(struct dma_pool *pool, gfp_t mem_flags,
             dma_addr_t *handle)
{
    unsigned long flags;
    struct dma_page *page;
    size_t offset;
    void *retval;

    might_sleep_if(gfpflags_allow_blocking(mem_flags));

    spin_lock_irqsave(&pool->lock, flags);
    list_for_each_entry(page, &pool->page_list, page_list) {
        if (page->offset < pool->allocation)
            goto ready;
    }

    /* pool_alloc_page() might sleep, so temporarily drop &pool->lock */
    spin_unlock_irqrestore(&pool->lock, flags);

    page = pool_alloc_page(pool, mem_flags & (~__GFP_ZERO));
    if (!page)
        return NULL;

    spin_lock_irqsave(&pool->lock, flags);

    list_add(&page->page_list, &pool->page_list);
 ready:
    page->in_use++;
    offset = page->offset;
    page->offset = *(int *)(page->vaddr + offset);
    retval = offset + page->vaddr;
    *handle = offset + page->dma;
    spin_unlock_irqrestore(&pool->lock, flags);

    if (mem_flags & __GFP_ZERO)
        memset(retval, 0, pool->size);

    return retval;
}
EXPORT_SYMBOL(dma_pool_alloc);

static inline bool is_page_busy(struct dma_page *page)
{
    return page->in_use != 0;
}

static void pool_free_page(struct dma_pool *pool, struct dma_page *page)
{
    dma_addr_t dma = page->dma;
    dma_free_coherent(pool->dev, pool->allocation, page->vaddr, dma);
    list_del(&page->page_list);
    kfree(page);
}

/**
 * dma_pool_destroy - destroys a pool of dma memory blocks.
 * @pool: dma pool that will be destroyed
 * Context: !in_interrupt()
 *
 * Caller guarantees that no more memory from the pool is in use,
 * and that nothing will try to use the pool after this call.
 */
void dma_pool_destroy(struct dma_pool *pool)
{
    bool empty = false;

    if (unlikely(!pool))
        return;

    mutex_lock(&pools_reg_lock);
    mutex_lock(&pools_lock);
    list_del(&pool->pools);
    if (pool->dev && list_empty(&pool->dev->dma_pools))
        empty = true;
    mutex_unlock(&pools_lock);
    if (empty)
        device_remove_file(pool->dev, &dev_attr_pools);
    mutex_unlock(&pools_reg_lock);

    while (!list_empty(&pool->page_list)) {
        struct dma_page *page;
        page = list_entry(pool->page_list.next,
                  struct dma_page, page_list);
        if (is_page_busy(page)) {
            if (pool->dev)
                dev_err(pool->dev,
                    "dma_pool_destroy %s, %p busy\n",
                    pool->name, page->vaddr);
            else
                pr_err("dma_pool_destroy %s, %p busy\n",
                       pool->name, page->vaddr);
            /* leak the still-in-use consistent memory */
            list_del(&page->page_list);
            kfree(page);
        } else
            pool_free_page(pool, page);
    }

    kfree(pool);
}
EXPORT_SYMBOL(dma_pool_destroy);

static struct dma_page *pool_find_page(struct dma_pool *pool, dma_addr_t dma)
{
    struct dma_page *page;

    list_for_each_entry(page, &pool->page_list, page_list) {
        if (dma < page->dma)
            continue;
        if ((dma - page->dma) < pool->allocation)
            return page;
    }
    return NULL;
}

/**
 * dma_pool_free - put block back into dma pool
 * @pool: the dma pool holding the block
 * @vaddr: virtual address of block
 * @dma: dma address of block
 *
 * Caller promises neither device nor driver will again touch this block
 * unless it is first re-allocated.
 */
void dma_pool_free(struct dma_pool *pool, void *vaddr, dma_addr_t dma)
{
    struct dma_page *page;
    unsigned long flags;
    unsigned int offset;

    spin_lock_irqsave(&pool->lock, flags);
    page = pool_find_page(pool, dma);
    if (!page) {
        spin_unlock_irqrestore(&pool->lock, flags);
        if (pool->dev)
            dev_err(pool->dev,
                "dma_pool_free %s, %p/%lx (bad dma)\n",
                pool->name, vaddr, (unsigned long)dma);
        else
            pr_err("dma_pool_free %s, %p/%lx (bad dma)\n",
                   pool->name, vaddr, (unsigned long)dma);
        return;
    }

    offset = vaddr - page->vaddr;
    page->in_use--;
    *(int *)vaddr = page->offset;
    page->offset = offset;
    /*
     * Resist a temptation to do
     *    if (!is_page_busy(page)) pool_free_page(pool, page);
     * Better have a few empty pages hang around.
     */
    spin_unlock_irqrestore(&pool->lock, flags);
}
EXPORT_SYMBOL(dma_pool_free);


