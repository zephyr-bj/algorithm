#include <iostream>
#include <vector>
#include <stdexcept>

class MinHeap {
private:
    std::vector<int> heap;

    void bubbleUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent]) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void bubbleDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left] < heap[smallest])
                smallest = left;
            if (right < size && heap[right] < heap[smallest])
                smallest = right;

            if (smallest != index) {
                std::swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    // Insert a new element
    void push(int val) {
        heap.push_back(val);
        bubbleUp(heap.size() - 1);
    }

    // Remove the minimum element (root)
    void pop() {
        if (heap.empty()) throw std::out_of_range("Heap is empty");
        
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            bubbleDown(0);
        }
    }

    // Get the minimum element
    int top() {
        if (heap.empty()) throw std::out_of_range("Heap is empty");
        return heap[0];
    }

    bool empty() { return heap.empty(); }
};

int main() {
    MinHeap mh;
    mh.push(10);
    mh.push(5);
    mh.push(20);
    mh.push(2);

    std::cout << "Top element: " << mh.top() << std::endl; // Should be 2

    mh.pop();
    std::cout << "Top after one pop: " << mh.top() << std::endl; // Should be 5

    return 0;
}
