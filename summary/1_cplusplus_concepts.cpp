#include <iostream>
#include <unordered_map>
#include <string>
#include <unistd.h> // for sleep()
#include <new> // Required for placement new
#include <memory_resource> // For pmr types

// new
//
template<typename T, typename... Args>
T* newElement(std::pmr::synchronized_pool_resource &pool_resource, Args&&... args) {
    T* p = nullptr;
    if ((p = reinterpret_cast<T*>(pool_resource.allocate(sizeof(T)))) != nullptr)
        new(p) T(std::forward<Args>(args)...);

    return p;
}

template<typename T>
void deleteElement(std::pmr::synchronized_pool_resource &pool_resource, T * p) {
    if (p) {
        p->~T();
        pool_resource.deallocate(reinterpret_cast<void*>(p), sizeof(T));
    }
}

class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "Constructor called, value = " << value << std::endl;
    }
    ~MyClass() {
        std::cout << "Destructor called, value = " << value << std::endl;
    }
private:
    int value;
};

void test_pla_new() {
    char buffer[sizeof(MyClass)];
    MyClass* obj1 = new (buffer) MyClass(10);
    sleep(1); // or do something else
    obj1->~MyClass();

    std::pmr::synchronized_pool_resource pool_resource;
    MyClass* obj2 = newElement<MyClass>(pool_resource,  11);
    sleep(1); // or do something else
    deleteElement<MyClass>(pool_resource, obj2);
}

enum class test_type{
    PLA_NEW,
};

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, test_type>test_map;
    test_map["pla_new"] = test_type::PLA_NEW;

    if (argc < 2) {
        printf("please enter test option\n");
	return 1;
    }
    auto it = test_map.find(std::string(argv[1]));
    if (it == test_map.end()) {
        printf("test '%s' is not supported\n", argv[1]);
	return 1;
    }
    test_type test = it->second;
    switch (test) {
        case test_type::PLA_NEW:
            test_pla_new();
            break;
        default:
	    printf("test function not implemented for '%s'\n", argv[1]);
	    break;
    }

    return 0;
}
