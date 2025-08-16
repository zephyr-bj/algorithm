#include <iostream>
#include <unordered_map>
#include <string>
#include <unistd.h> // for sleep()
#include <new> // Required for placement new
#include <memory_resource> // For pmr types

#include <cstdarg> // Required for va_list, va_start, va_arg, va_end

// pla_new
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

// variadic function
//
void print_values(int count, ...) {
    va_list args;
    va_start(args, count); // Initialize va_list with the last fixed argument

    for (int i = 0; i < count; ++i) {
        int value = va_arg(args, int); // Retrieve argument as an int
        std::cout << value << " ";
    }
    va_end(args); // Clean up va_list
    std::cout << std::endl;
}

void test_variadic_function() {
    print_values(3, 10, 20, 30);
    print_values(2, 5, 15);
}

// variadic template
//
void print_pack() {
    std::cout << std::endl;
}

template<typename T, typename... Args>
void print_pack(T first_arg, Args... rest_of_args) {
    std::cout << first_arg << " ";
    print_pack(rest_of_args...); // Recursively call with remaining arguments
}

void test_variadic_template() {
    print_pack(1, "hello", 3.14);
    print_pack('a', true);
}

enum class test_type{
    PLA_NEW,
    VAR_FUN,
    VAR_TPL,
};

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, test_type>test_map;
    test_map["pla_new"] = test_type::PLA_NEW;
    test_map["variadic_fun"] = test_type::VAR_FUN;
    test_map["variadic_tpl"] = test_type::VAR_TPL;

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
        case test_type::VAR_FUN:
            test_variadic_function();
            break;
        case test_type::VAR_TPL:
            test_variadic_template();
            break;
        default:
	    printf("test function not implemented for '%s'\n", argv[1]);
	    break;
    }

    return 0;
}
