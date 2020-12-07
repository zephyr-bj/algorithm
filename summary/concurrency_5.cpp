/* print in order [4] : (1114) print in order (1115) print alternatively (1116) print zero even odd (1195) print fizz buzz
 * group action [1] : (1117) build H2O
 */
#include <semaphore.h>
// (1114) print in order
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

// (1115) print alternatively
class FooBar {
private:
    int n;
    sem_t foodone;
    sem_t bardone;
public:
    FooBar(int n) {
        this->n = n;
        sem_init(&foodone, 0, 0);
        sem_init(&bardone, 0, 1);
    }

    void foo(function<void()> printFoo) {      
        for (int i = 0; i < n; i++) {
            sem_wait(&bardone);
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            sem_post(&foodone);     
        }
    }

    void bar(function<void()> printBar) {        
        for (int i = 0; i < n; i++) {
            sem_wait(&foodone);
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            sem_post(&bardone);
        }
    }
};

// (1116) print zero even odd
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

// (1195) print fizz buzz
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

// (1117) build H2O
class H2O {
    
public:
    sem_t semM;
    sem_t semO;
    sem_t semH;
    sem_t mdone;
    int cntH;
    int cntO;
    H2O() {
        sem_init(&semM,0,1);//used as a mutex
        sem_init(&mdone,0,0);
        sem_init(&semH,0,2);
        sem_init(&semO,0,1);
        cntH=0; cntO=0;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        sem_wait(&semH);
        sem_wait(&semM);
        cntH++;
        if(cntH<2 || cntO<1){
            sem_post(&semM);
            sem_wait(&mdone);
        }else{
            cntH=0;cntO=0;
            sem_post(&semM);
            sem_post(&mdone);
            sem_post(&mdone);
        }
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        sem_post(&semH);
    }
    
    void oxygen(function<void()> releaseOxygen) {
        sem_wait(&semO);
        sem_wait(&semM);
        cntO++;
        if(cntH<2 || cntO <1){
            sem_post(&semM);
            sem_wait(&mdone);
        }else{
            cntH=0; cntO=0;
            sem_post(&semM);
            sem_post(&mdone);
            sem_post(&mdone);
        }
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        sem_post(&semO);
    }
};

// the non-blocking "sem_trywait" solution
class H2O {
public:
    sem_t sem_h;
    sem_t sem_o;
    sem_t sem_c;
    sem_t sem_m;
    H2O() {
        sem_init(&sem_h,0,2);
        sem_init(&sem_o,0,1);
        sem_init(&sem_c,0,0);
        sem_init(&sem_m,0,1);
    }

    void hydrogen(function<void()> releaseHydrogen) {
        sem_wait(&sem_h);
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        if(sem_trywait(&sem_m)!=0) sem_post(&sem_c);
    }

    void oxygen(function<void()> releaseOxygen) {
        sem_wait(&sem_o);
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        sem_wait(&sem_c);
        sem_post(&sem_m);
        sem_post(&sem_o);
        sem_post(&sem_h);
        sem_post(&sem_h);
    }
};
