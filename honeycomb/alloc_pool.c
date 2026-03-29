#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Block {
    struct Block* next;
} Block;

typedef struct {
    size_t blockSize;
    size_t numBlocks;
    void* poolMemory;
    Block* freeList;
} MemoryPool;

// Initialize the pool
MemoryPool* pool_create(size_t blockSize, size_t numBlocks) {
    // Ensure block size is at least large enough to hold a pointer
    if (blockSize < sizeof(Block)) blockSize = sizeof(Block);

    MemoryPool* pool = malloc(sizeof(MemoryPool));
    pool->blockSize = blockSize;
    pool->numBlocks = numBlocks;
    pool->poolMemory = malloc(blockSize * numBlocks);
    pool->freeList = (Block*)pool->poolMemory;

    // Link all blocks together in a free list
    Block* current = pool->freeList;
    for (size_t i = 0; i < numBlocks - 1; i++) {
        current->next = (Block*)((uint8_t*)current + blockSize);
        current = current->next;
    }
    current->next = NULL; // Last block

    return pool;
}

// Allocate a block from the pool (O(1) complexity)
void* pool_alloc(MemoryPool* pool) {
    if (pool->freeList == NULL) return NULL; // Out of memory

    Block* block = pool->freeList;
    pool->freeList = block->next;
    return (void*)block;
}

// Deallocate a block back to the pool (O(1) complexity)
void pool_free(MemoryPool* pool, void* ptr) {
    if (ptr == NULL) return;

    Block* block = (Block*)ptr;
    block->next = pool->freeList;
    pool->freeList = block;
}

// Clean up the entire pool
void pool_destroy(MemoryPool* pool) {
    free(pool->poolMemory);
    free(pool);
}

int main() {
    MemoryPool* myPool = pool_create(32, 10); // 10 blocks of 32 bytes

    void* addr1 = pool_alloc(myPool);
    printf("Allocated at: %p\n", addr1);

    pool_free(myPool, addr1);
    printf("Freed addr1 back to pool.\n");

    pool_destroy(myPool);
    return 0;
}
