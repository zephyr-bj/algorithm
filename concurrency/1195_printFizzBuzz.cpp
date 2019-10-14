#include <semaphore.h>
class FizzBuzz {
private:
    int n;
    int x;
    sem_t semN;
    sem_t semF;
    sem_t semB;
    sem_t semFB;
public:
    FizzBuzz(int n) {
        this->n = n;
        x = 1;
        sem_init(&semN, 0, 1);
        sem_init(&semF, 0, 0);
        sem_init(&semB, 0, 0);
        sem_init(&semFB, 0, 0);
    }

    void fizzbuzzRelease(){
        if(x>n){
            sem_post(&semN);
            sem_post(&semF);
            sem_post(&semB);
            sem_post(&semFB);
        }
        if(((x%3)==0)&&((x%5)==0)){
            sem_post(&semFB);
        }else if((x%3)==0){
            sem_post(&semF);
        }else if((x%5)==0){
            sem_post(&semB);
        }else{
            sem_post(&semN);
        }
    }
    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(1){
            sem_wait(&semF);
            if(x>n)break;
            printFizz();
            x++;
            fizzbuzzRelease();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(1){
            sem_wait(&semB);
            if(x>n)break;
            printBuzz();
            x++;
            fizzbuzzRelease();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while(1){
            sem_wait(&semFB);
            if(x>n)break;
            printFizzBuzz();
            x++;
            fizzbuzzRelease();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(1){
            sem_wait(&semN);
            if(x>n)break;
            printNumber(x);
            x++;
            fizzbuzzRelease();
        }
    }
};
