#include <semaphore.h>
class Foo {
public:
    sem_t firstdone;
    sem_t seconddone;
    Foo() {
        sem_init(&firstdone, 0, 0);
        sem_init(&seconddone, 0, 0);
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem_post(&firstdone);
    }

    void second(function<void()> printSecond) {
        sem_wait(&firstdone);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        sem_post(&seconddone);
    }

    void third(function<void()> printThird) {
        sem_wait(&seconddone);
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
