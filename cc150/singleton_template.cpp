#include <iostream>
#include <pthread.h>

using namespace std;

// singleton temple, only instance once
template <typename T>
class Singleton{
private:
    static pthread_mutex_t lock;
    static T* object;
protected:
    Singleton() { };
public:
    static T* Instance();
};

template <typename T>
T* Singleton<T>::Instance(){
    if (object == NULL){// if it is not initialized, try to lock it
        pthread_mutex_lock(&lock); //wait for the lock
       // for the same batch of thread wait for the lock, only the first one needs to initialize the instances. 
        if (object == NULL){ 
            object = new T;
        }
        pthread_mutex_unlock(&lock);
    }
    return object;
}
class Foo{
    
};


int main(){
    Foo* singleton_foo = Singleton<Foo>::Instance();
    return 0;
}
