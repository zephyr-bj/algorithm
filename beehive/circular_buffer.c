//===================================================================
// File: circular_buffer.cpp
//
// Desc: A Circular Buffer implementation in C++.
//
// Copyright © 2019 Edwin Cloud. All rights reserved.
//
//===================================================================
//copied from https://gist.github.com/edwintcloud/d547a4f9ccaf7245b06f0e8782acefaa#file-circular_buffer-cpp

#include <memory>	// for std::unique_ptr
#include <stdexcept>	// Required for std::runtime_error

template <class T> 
class Circular_Buffer {
private:

  std::unique_ptr<T[]> buffer; // using a smart pointer is safer (and we don't
                               // have to implement a destructor)
  size_t head = 0;             // size_t is an unsigned long
  size_t tail = 0;
  size_t max_size;
  T empty_item; // we will use this to clear data
public:
  Circular_Buffer<T>(size_t max_size)
      : buffer(std::unique_ptr<T[]>(new T[max_size])), max_size(max_size){};

  void enqueue(T item) {
    if (is_full())
      throw std::runtime_error("buffer is full"); 
    // or we could just return a error code to prevent termination by runtime_err
    buffer[tail] = item;
    tail = (tail + 1) % max_size;
  }

  void enqueue2(T item) {
    buffer[tail] = item;
    if (is_full()) {
      head = (head + 1) % max_size;
    }
    tail = (tail + 1) % max_size;
  }

  T dequeue() {
    if (is_empty())
      throw std::runtime_error("buffer is empty");
    // or we could just return a null pointer to prevent termination by runtime_err
    T item = buffer[head];
    T empty;
    buffer[head] = empty_item;
    head = (head + 1) % max_size;
    return item;
  }

  T front() { return buffer[head]; }

  bool is_empty() { return head == tail; }

  bool is_full() { return head == (tail + 1) % max_size; }

  size_t size() {
    if (tail >= head)
      return tail - head;
    return max_size - head - tail;
  }
};

//---------------------------------------------------------------
// Main Function
//---------------------------------------------------------------
int main() {

  Circular_Buffer<uint32_t> cb(10);

  printf("\n === CircularBuffer Test ===\n");
  printf("Size: %zu\n", cb.size());

  uint32_t x = 1;
  printf("Enqueue 1, val: %d\n", x);
  cb.enqueue(x);
  printf("Size: %zu\n", cb.size());
  x = 2;
  printf("Enqueue 1, val: %d\n", x);
  cb.enqueue(x);
  printf("Size: %zu\n", cb.size());
  printf("Enqueue 1, val: %d\n", x);
  cb.enqueue(x);
  printf("Size: %zu\n", cb.size());
  x = cb.dequeue();
  printf("Dequeue: %d\n", x);
  printf("Size: %zu\n", cb.size());
  x = cb.dequeue();
  printf("Dequeue: %d\n", x);
  printf("Size: %zu\n", cb.size());
  x = cb.dequeue();
  printf("Dequeue: %d\n", x);
  printf("Size: %zu\n", cb.size());
  x = cb.dequeue();
  printf("Dequeue: %d\n", x);
  printf("Size: %zu\n", cb.size());
  printf("Empty: %d\n", cb.is_empty());

}
