#include <semaphore.h>
class ZeroEvenOdd {
private:
    int n;
public:
    sem_t print_zero;
    sem_t print_odd;
    sem_t print_even;
    ZeroEvenOdd(int n) {
        this->n = n;
        sem_init(&print_zero, 0, 1);
        sem_init(&print_odd, 0, 0);
        sem_init(&print_even, 0, 0);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for(int i=1; i<=n; i++){
            sem_wait(&print_zero);
            printNumber(0);
            if(i%2)
                sem_post(&print_odd);
            else
                sem_post(&print_even);
        }
    }

    void even(function<void(int)> printNumber) {
        for(int i=2; i<=n; i+=2){
            sem_wait(&print_even);
            printNumber(i);
            if(i<n)sem_post(&print_zero);
        }
    }

    void odd(function<void(int)> printNumber) {
        for(int i=1; i<=n; i+=2){
            sem_wait(&print_odd);
            printNumber(i);
            if(i<n)sem_post(&print_zero);
        }
    }
};
