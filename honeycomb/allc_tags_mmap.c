#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* ================= CONFIG ================= */

#define ALIGNMENT 16
#define ALIGN(x) (((x) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

#define WSIZE sizeof(size_t)
#define DSIZE (2 * WSIZE)

//#define ARENA_SIZE   (1 << 20)      // 1 MB arenas
#define ARENA_SIZE   (1 << 7)      // 128 B arenas
#define MMAP_THRESH  (128 * 1024)   // 128 KB large alloc threshold
#define MIN_BLOCK    (4 * WSIZE)    // hdr + prev + next + ftr

/* flags in low bits */
#define ALLOC  1UL
#define MMAPED 2UL
#define FLAG_MASK 0x3UL
#define SIZE_MASK (~FLAG_MASK)

#define PACK(size, flags) ((size) | (flags))
#define GET(p) (*(size_t *)(p))
#define PUT(p, val) (*(size_t *)(p) = (val))
#define GET_SIZE(p) (GET(p) & SIZE_MASK)
#define GET_FLAGS(p) (GET(p) & FLAG_MASK)
#define GET_ALLOC(p) (GET(p) & ALLOC)
#define GET_MMAP(p)  (GET(p) & MMAPED)

/* Block navigation (bp points to header) */
#define HDRP(bp) ((char *)(bp))
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - WSIZE)
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_FTRP(bp) ((char *)(bp) - WSIZE)
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(PREV_FTRP(bp)))

/* Free list pointers stored in payload */
#define NEXT_FREE(bp) (*(void **)((char *)(bp) + WSIZE))
#define PREV_FREE(bp) (*(void **)((char *)(bp) + WSIZE + sizeof(void *)))

/* ================= GLOBALS ================= */

static void *free_list = NULL;

/* ================= FREE LIST ================= */

static void remove_free(void *bp)
{
    void *prev = PREV_FREE(bp);
    void *next = NEXT_FREE(bp);

    if (prev)
        NEXT_FREE(prev) = next;
    else
        free_list = next;

    if (next)
        PREV_FREE(next) = prev;
}

static void insert_free(void *bp)
{
    NEXT_FREE(bp) = free_list;
    PREV_FREE(bp) = NULL;

    if (free_list)
        PREV_FREE(free_list) = bp;

    free_list = bp;
}

static void *find_fit(size_t asize)
{
    void *bp = free_list;

    while (bp) {
        if (GET_SIZE(HDRP(bp)) >= asize)
            return bp;
        bp = NEXT_FREE(bp);
    }
    return NULL;
}

/* ================= COALESCE ================= */

static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(PREV_FTRP(bp));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));
    printf("prev_allc = %ld, next_allc = %ld\n", prev_alloc, next_alloc);

    if (!prev_alloc) {
        void *prev = PREV_BLKP(bp);
        remove_free(prev);
        size += GET_SIZE(HDRP(prev));
        bp = prev;
    }

    if (!next_alloc) {
        void *next = NEXT_BLKP(bp);
        remove_free(next);
        size += GET_SIZE(HDRP(next));
    }
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    insert_free(bp);
    return bp;
}

/* ================= ARENA EXTEND ================= */

static void arena_extend(size_t size)
{
    size = ALIGN(size);

    void *mem = mmap(NULL, size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS,
                     -1, 0);

    if (mem == MAP_FAILED)
        return;

    PUT(mem + (0 * WSIZE), PACK(DSIZE, 1));   // prologue header
    PUT(mem + (1 * WSIZE), PACK(DSIZE, 1));   // prologue footer
    PUT(mem + size - WSIZE, PACK(0, 1));      // epilogue header

    /* create single large free block */
    size -= 3 * WSIZE;
    PUT(mem + (2 * WSIZE), PACK(size, 0));
    PUT((char *)mem + (2 * WSIZE) + size - WSIZE, PACK(size, 0));
    insert_free(mem + 2 * WSIZE);
}

/* ================= PLACE ================= */

static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));
    remove_free(bp);

    if (csize - asize >= MIN_BLOCK) {
        printf("csize %ld, asize %ld, min_blk %ld, split = true\n",
            csize, asize, MIN_BLOCK);
        /* split */
        PUT(HDRP(bp), PACK(asize, ALLOC));
        PUT(FTRP(bp), PACK(asize, ALLOC));

        void *next = NEXT_BLKP(bp);
        PUT(HDRP(next), PACK(csize - asize, 0));
        PUT(FTRP(next), PACK(csize - asize, 0));
        insert_free(next);
    } else {
        printf("csize %ld, asize %ld, min_blk %ld, split = false\n",
            csize, asize, MIN_BLOCK);
        PUT(HDRP(bp), PACK(csize, ALLOC));
        PUT(FTRP(bp), PACK(csize, ALLOC));
    }
}

/* ================= MALLOC ================= */

void *my_malloc(size_t size)
{
    if (size == 0)
        return NULL;

    size = ALIGN(size);

    /* large allocation → direct mmap */
    if (size >= MMAP_THRESH) {
        size_t total = size + WSIZE;
        void *mem = mmap(NULL, total,
                         PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANONYMOUS,
                         -1, 0);
        if (mem == MAP_FAILED)
            return NULL;

        PUT(mem, PACK(total, ALLOC | MMAPED));
        return (char *)mem + WSIZE;
    }

    size_t asize = ALIGN(size + DSIZE);

    void *bp = find_fit(asize);
    if (!bp) {
        if (asize > ARENA_SIZE) {
            return NULL;
        }
        arena_extend(ARENA_SIZE);
        bp = find_fit(asize);
        if (!bp)
            return NULL;
    }
    place(bp, asize);
    return (char *)bp + WSIZE;
}

/* ================= FREE ================= */

void my_free(void *ptr)
{
    if (!ptr)
        return;

    void *hdr = (char *)ptr - WSIZE;
    size_t flags = GET_FLAGS(hdr);
    size_t size = GET_SIZE(hdr);

    if (flags & MMAPED) {
        munmap(hdr, size);
        return;
    }

    PUT(HDRP(hdr), PACK(size, 0));
    PUT(FTRP(hdr), PACK(size, 0));
    coalesce(hdr);
}

/* ================= REALLOC ================= */

void *my_realloc(void *ptr, size_t size)
{
    if (!ptr)
        return my_malloc(size);

    if (size == 0) {
        my_free(ptr);
        return NULL;
    }

    void *hdr = (char *)ptr - WSIZE;
    size_t old_size = GET_SIZE(hdr) - DSIZE;

    if (size <= old_size)
        return ptr;

    void *newp = my_malloc(size);
    if (!newp)
        return NULL;

    memcpy(newp, ptr, old_size);
    my_free(ptr);
    return newp;
}

/* ================= TEST ================= */

int main()
{
    void *a = my_malloc(64);       // arena size 128 byte, 
                                   // prologue + epilogue 24 bytes
                                   // 64 + DSIZE takes 80 bytes,
    // when this freed, its coalesce process will be guarded by the epilogue 
    //void *b = my_malloc(200);
    void *b = my_malloc(16);       // takes 32 bytes
    void *c = my_malloc(300000);   // mmap allocation

    printf("a=%p b=%p c=%p\n", a, b, c);

    my_free(b);
    my_free(a);
    my_free(c);

    void *d = my_malloc(128);
    if (d !=NULL) {
        printf("d=%p\n", d);
    }

    my_free(d);

    printf("Allocator OK\n");
    return 0;
}
