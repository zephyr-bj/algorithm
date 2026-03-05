#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/*
1. Three sets of definitions: 6 constants + 5 value operators + 7 pointer operators
2. Three Linked list functions: insert_block + remove_block + find_fit
3. Three Helper functions: coalesce + place + extend_heap
5. Three API function: mm_init + mm_alloc + mm_free
*/

/* ================= CONFIG ================= */
/* the constants */
#define ALIGNMENT 16
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

#define WSIZE sizeof(size_t)
#define DSIZE (2 * WSIZE)
#define CHUNK_SIZE (1 << 12)   // 4 KB
#define MIN_BLOCK_SIZE (4 * WSIZE)  // hdr + prev + next + ftr

/* the values */
#define GET(p) (*(size_t *)(p))
#define PUT(p, val) (*(size_t *)(p) = (val))

#define PACK(size, alloc) ((size) | (alloc))
#define GET_SIZE(p) (GET(p) & ~(ALIGNMENT-1))
#define GET_ALLOC(p) (GET(p) & 0x1)

/* the pointers */
#define HDRP(bp) ((char *)(bp))
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - WSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(PREV_FTRP(bp)))
#define PREV_FTRP(bp) ((char *)(bp) - WSIZE)

#define NEXT_FREE(bp) (*(void **)((char *)(bp) + WSIZE))
#define PREV_FREE(bp) (*(void **)((char *)(bp) + WSIZE + sizeof(void *)))

/* ================= GLOBALS ================= */

static void *heap_listp = NULL;     // for heap traversal and check
static void *free_list_head = NULL;

/* ================= FREE LIST ================= */

static void remove_free(void *bp)
{
    void *prev = PREV_FREE(bp);
    void *next = NEXT_FREE(bp);

    if (prev)
        NEXT_FREE(prev) = next;
    else
        free_list_head = next;

    if (next)
        PREV_FREE(next) = prev;
}

static void insert_free(void *bp)
{
    NEXT_FREE(bp) = free_list_head;
    PREV_FREE(bp) = NULL;

    if (free_list_head)
        PREV_FREE(free_list_head) = bp;

    free_list_head = bp;
}

static void *find_fit(size_t asize)
{
    void *bp = free_list_head;

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

    if (prev_alloc && next_alloc) {
        insert_free(bp);
        return bp;
    }

    if (!next_alloc) {
        void *next = NEXT_BLKP(bp);
        remove_free(next);
        size += GET_SIZE(HDRP(next));
    }

    if (!prev_alloc) {
        void *prev = PREV_BLKP(bp);
        remove_free(prev);
        size += GET_SIZE(HDRP(prev));
        bp = prev;
    }

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    insert_free(bp);
    return bp;
}

/* ================= PLACE ================= */

static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));
    remove_free(bp);

    if ((csize - asize) >= MIN_BLOCK_SIZE) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));

        void *next = NEXT_BLKP(bp);
        PUT(HDRP(next), PACK(csize - asize, 0));
        PUT(FTRP(next), PACK(csize - asize, 0));
        insert_free(next);
    }
    else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}

/* ================= EXTEND HEAP ================= */

static void *extend_heap(size_t size)
{
    size = ALIGN(size);

    void *bp = sbrk(size);
    if (bp == (void *)-1)
        return NULL;

    /* Overwrite old epilogue header */
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));

    /* New epilogue header */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    return coalesce(bp);
}

/* ================= INIT ================= */

int mm_init(void)
{
    /* Allocate space for padding, prologue, epilogue */
    if ((heap_listp = sbrk(4 * WSIZE)) == (void *)-1)
        return -1;

    PUT(heap_listp, 0);                              // alignment padding
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));   // prologue header
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));   // prologue footer
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));       // epilogue header

    heap_listp += (2 * WSIZE);
    free_list_head = NULL;

    if (extend_heap(CHUNK_SIZE) == NULL)
        return -1;

    return 0;
}

/* ================= MALLOC ================= */

void *mm_malloc(size_t size)
{
    if (size == 0)
        return NULL;

    size_t asize = ALIGN(size + DSIZE);

    void *bp = find_fit(asize);
    if (!bp) {
        size_t extend_size = (asize > CHUNK_SIZE) ? asize : CHUNK_SIZE;
        bp = extend_heap(extend_size);
        if (!bp)
            return NULL;
    }

    place(bp, asize);
    return (char *)bp + WSIZE;
}

/* ================= FREE ================= */

void mm_free(void *ptr)
{
    if (!ptr)
        return;

    void *bp = (char *)ptr - WSIZE;
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

/* ================= TEST ================= */

int main()
{
    if (mm_init() == -1) {
        printf("Init failed\n");
        return 1;
    }

    void *a = mm_malloc(63);
    void *b = mm_malloc(200);
    void *c = mm_malloc(50);

    printf("Allocated: %p %p %p\n", a, b, c);

    mm_free(b);
    mm_free(a);
    mm_free(c);

    void *d = mm_malloc(300);
    printf("After free + coalesce: %p\n", d);

    printf("Allocator test complete\n");
    return 0;
}
