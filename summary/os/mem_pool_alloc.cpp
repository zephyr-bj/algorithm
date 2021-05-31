/* http://dmitrysoshnikov.com/compilers/writing-a-pool-allocator/ */
class PoolAllocator {
 public:
  PoolAllocator(size_t chunksPerBlock)
    : mChunksPerBlock(chunksPerBlock) {}
 
  void *allocate(size_t size);
  void deallocate(void *ptr, size_t size);
 
 private:
  size_t mChunksPerBlock;
  Chunk *mAlloc = nullptr;
  Chunk *allocateBlock();
};

Chunk *PoolAllocator::allocateBlock(size_t chunkSize) {
  cout << "\nAllocating block (" << mChunksPerBlock << " chunks):\n\n";
 
  size_t blockSize = mChunksPerBlock * chunkSize;
  Chunk *blockBegin = reinterpret_cast<Chunk *>(malloc(blockSize));
  Chunk *chunk = blockBegin;
  for (int i = 0; i < mChunksPerBlock - 1; ++i) {
    chunk->next =
        reinterpret_cast<Chunk *>(reinterpret_cast<char *>(chunk) + chunkSize);
    chunk = chunk->next;
  }
  chunk->next = nullptr;
  return blockBegin;
}

void *PoolAllocator::allocate(size_t size) {
  if (mAlloc == nullptr) {
    mAlloc = allocateBlock(size);
  }
  Chunk *freeChunk = mAlloc;
  mAlloc = mAlloc->next; 
  return freeChunk;
}

void PoolAllocator::deallocate(void *chunk, size_t size) {
  reinterpret_cast<Chunk *>(chunk)->next = mAlloc;
  mAlloc = reinterpret_cast<Chunk *>(chunk);
}
//C++ allows overriding default behavior of the new and delete operators. 
struct Object {
  // Object data, 16 bytes:
  uint64_t data[2];
  static PoolAllocator allocator;
  static void *operator new(size_t size) {
    return allocator.allocate(size);
  }
  static void operator delete(void *ptr, size_t size) {
    return allocator.deallocate(ptr, size);
  }
};
