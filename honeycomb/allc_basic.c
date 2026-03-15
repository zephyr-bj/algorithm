#include <unistd.h> // for skrb()
#include <string.h>
#include <stdio.h>

// compile with gcc allc_basic.c -o allc

// Has no splitting/coalescing
// Not thread-safe
// Align the size with power of 2 is important

typedef struct block {
    size_t size;
    int free;
    struct block *next;
} block_t;

static block_t *free_list = NULL;

#define ALIGN 16
#define ALIGN_UP(x) (((x) + ALIGN - 1) & ~(ALIGN - 1))

block_t *find_free(size_t size) {
    block_t *curr = free_list;
    while (curr) {
        if (curr->free && curr->size >= size)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

block_t *request_space(block_t *last, size_t size) {
    block_t *block = sbrk(0);
    void *req = sbrk(sizeof(block_t) + size);
    if (req == (void *)-1)
        return NULL;

    if (last)
        last->next = block;

    block->size = size;
    block->free = 0;
    block->next = NULL;
    return block;
}

void *my_alloc(size_t size) {
    if (size == 0)
        return NULL;
// ALIGN_UP is important, otherwise, sbrk may not work as expected. 
    size = ALIGN_UP(size);
    block_t *block;

    if (!free_list) {
        block = request_space(NULL, size);
        free_list = block;
    } else {
        block_t *last = free_list;
        block = find_free(size);
        if (!block) {
            while (last->next)
                last = last->next;
            block = request_space(last, size);
        } else {
            block->free = 0;
        }
    }
    return (block + 1);
}

void my_free(void *ptr) {
    if (!ptr)
        return;

    block_t *block = (block_t *)ptr - 1;
    block->free = 1;
}

void traverseList() {
    block_t *cur = free_list;
    while(cur!=NULL) {
        printf("size(%ld)free(%d)|", cur->size, cur->free);
        cur=cur->next;
    }
    printf("\n");
}

int main()
{
    void * x = my_alloc(15);
    void * y = my_alloc(64);
    void * z = my_alloc(100);
    
    traverseList();
    my_free(y);
    traverseList();
    my_free(z);
    traverseList();
    void * a = my_alloc(30);
    my_free(x);
    traverseList();
    my_free(a);
    traverseList();

    return 0;
}
