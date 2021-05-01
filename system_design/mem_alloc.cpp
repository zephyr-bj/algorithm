include <unistd.h>   // for sbrk

struct Block {
  // -------------------------------------
  // 1. Object header
  /**
   * Block size.
   */
  size_t size;
  /**
   * Whether this block is currently used.
   */
  bool used;
  /**
   * Next block in the list.
   */
  Block *next;
 
  // -------------------------------------
  // 2. User data
  /**
   * Payload pointer.
   */
  word_t data[1];
};

static Block *heapStart = nullptr;
static auto top = heapStart;

inline size_t align(size_t n) {
  return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}

/**
 * Returns total allocation size, reserving in addition the space for
 * the Block structure (object header + first data word).
 *
 * Since the `word_t data[1]` already allocates one word inside the Block
 * structure, we decrease it from the size request: if a user allocates
 * only one word, it's fully in the Block struct.
 */
inline size_t allocSize(size_t size) {
  return size + sizeof(Block) - sizeof(std::declval<Block>().data);
}
 
/**
 * Requests (maps) memory from OS.
 */
Block *requestFromOS(size_t size) {
  // Current heap break.
  auto block = (Block *)sbrk(0);                // (1)
  // OOM.
  if (sbrk(allocSize(size)) == (void *)-1) {    // (2)
    return nullptr;
  }
  return block;
}

/**
 * Allocates a block of memory of (at least) `size` bytes.
 */
word_t *alloc(size_t size) {
  size = align(size);
 
  // ---------------------------------------------------------
  // 1. Search for an available free block:
  if (auto block = findBlock(size)) {                   // (1)
    return block->data;
  }
  // ---------------------------------------------------------
  // 2. If block not found in the free list, request from OS:
  auto block = requestFromOS(size);
 
  block->size = size;
  block->used = true;
 
  // Init heap.
  if (heapStart == nullptr) {
    heapStart = block;
  }
 
  // Chain the blocks.
  if (top != nullptr) {
    top->next = block;
  }
 
  top = block;
 
  // User payload:
  return block->data;
}

/**
 * Frees a previously allocated block.
 */
void free(word_t *data) {
  auto block = getHeader(data);
  block->used = false;
}
