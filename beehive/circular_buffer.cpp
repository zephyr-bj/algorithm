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
#include <mutex>
#include <condition_variable>

template <class T> 
class CircBuf {
private:

	std::unique_ptr<T[]> buf;
	size_t head = 0;
	size_t tail = 0;
	size_t sz;
	std::mutex mtx;
    std::condition_variable cv;
public:
	CircBuf<T>(size_t size)
			: buf(std::unique_ptr<T[]>(new T[size])), sz(size){};

	void enqueue(T item) {
        {
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait(lk, [this]{return this->is_full() == false;});
		    if (is_full())
			    throw std::runtime_error("buffer is full"); 
    		buf[head] = item;
	    	head = (head + 1) % sz;
        }
        cv.notify_all();
	}

	T dequeue() {
        T item;
        {
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait(lk, [this]{return this->is_empty() == false;});
	    	if (is_empty())
		    	throw std::runtime_error("buffer is empty");
    		item = buf[tail];
	    	tail = (tail + 1) % sz;
        }
        cv.notify_all();
		return item;
	}

	T front() { return buf[head]; }

	bool is_empty() { return head == tail; }

	bool is_full() { return tail == (head + 1) % sz; }

	size_t size() {
		if (head >= tail)
			return head - tail;
		return sz - (tail - head);
	}
};

//---------------------------------------------------------------
// Main Function
//---------------------------------------------------------------
int main() {

	CircBuf<uint32_t> cb(10);

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
//	x = cb.dequeue();
//	printf("Dequeue: %d\n", x);
	printf("Size: %zu\n", cb.size());
	printf("Empty: %d\n", cb.is_empty());

}
