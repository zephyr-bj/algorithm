/* print in order [4] : (1114) print in order (1115) print alternatively (1116) print zero even odd (1195) print fizz buzz
 * group action [1] : (1117) build H2O
 * multiple locks [1]: (1226) dining philosophers
 */
#include <semaphore.h>
#include <mutex>
#include <condition_variable>
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
        printFirst();
        sem_post(&firstdone);
    }

    void second(function<void()> printSecond) {
        sem_wait(&firstdone);
        printSecond();
        sem_post(&seconddone);
    }

    void third(function<void()> printThird) {
        sem_wait(&seconddone);
        printThird();
    }
};

class Foo_2 {
public:
    Foo_2() {
        ready = 0;
    }
    int ready;
    std::mutex mtx;
    std::condition_variable cv;
    void first(function<void()> printFirst) {
        std::unique_lock<std::mutex>lock(mtx);
        printFirst();
        ready = 1;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        std::unique_lock<std::mutex>lock(mtx);
        cv.wait(lock, [this](){return this->ready == 1;});
        printSecond();
        ready=2;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        std::unique_lock<std::mutex>lock(mtx);
        cv.wait(lock, [this](){return this->ready == 2;});
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
        	printFoo();
            sem_post(&foodone);     
        }
    }

    void bar(function<void()> printBar) {        
        for (int i = 0; i < n; i++) {
            sem_wait(&foodone);
        	printBar();
            sem_post(&bardone);
        }
    }
};

class FooBar_2 {
private:
    int n;

public:
    FooBar_2(int n) {
        this->n = n;
        flag = 0;
    }
    std::mutex mtx;
    std::condition_variable cv;
    bool flag;
    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return this->flag == 0;});
        	printFoo();
            flag = 1;
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return this->flag == 1;});
        	printBar();
            flag = 0;
            cv.notify_one();
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

class ZeroEvenOdd {
private:
    int n;

public:
    std::mutex mtx;
    std::condition_variable cv;
    int i;
    unsigned int flag;
    ZeroEvenOdd(int n) {
        this->n = n;
        i = 1;
        flag = 0;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while( i <= n ) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return ((this->flag) % 2) == 0;});
            if (i <= n) {
                printNumber(0);
            }
            flag++;
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while ( i <= n ) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return ((this->flag) % 4) == 3;});
            if (i <= n) {
                printNumber(i);
            }
            flag++;
            i++;
            cv.notify_all();
        }       
    }

    void odd(function<void(int)> printNumber) {
        while ( i <= n ) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return ((this->flag) % 4) == 1;});
            if (i <= n) {
                printNumber(i);
            }
            flag++;
            i++;
            cv.notify_all();
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

    void fizz(function<void()> printFizz) {
        while(1){
            sem_wait(&semF);
            if(x>n)break;
            printFizz();
            x++;
            fizzbuzzRelease();
        }
    }

    void buzz(function<void()> printBuzz) {
        while(1){
            sem_wait(&semB);
            if(x>n)break;
            printBuzz();
            x++;
            fizzbuzzRelease();
        }
    }

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

class FizzBuzz_2 {
private:
    int n;
    int i;
    int done;
    std::mutex mtx;
    std::condition_variable cv;

public:
    FizzBuzz_2(int n) {
        this->n = n;
        i = 1;
        done = 0;
    }

    void fizz(function<void()> printFizz) {
        while ( done == 0 ) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return  (((i % 3) == 0) && ((i % 5) != 0)) || (done == 1);});
            if (done == 0) {
                printFizz();
                i++;
            }
            if (i > n) {
                done = 1;
            }
            cv.notify_all();
        }
    }

    void buzz(function<void()> printBuzz) {
        while ( done == 0 ) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return  (((i % 3) != 0) && ((i % 5) == 0)) || (done == 1);});
            if (done == 0) {
                printBuzz();
                i++;
            }
            if (i > n) {
                done = 1;
            }
            cv.notify_all();
        }
    }

	void fizzbuzz(function<void()> printFizzBuzz) {
        while ( done == 0 ) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return  (((i % 3) == 0) && ((i % 5) == 0)) || (done == 1);});
            if (done == 0) {
                printFizzBuzz();
                i++;
            }
            if (i > n) {
                done = 1;
            }
            cv.notify_all();
        }
    }

    void number(function<void(int)> printNumber) {
        while ( done == 0 ) {
            std::unique_lock<std::mutex>lock(mtx);
            cv.wait(lock, [this](){return  (((i % 3) != 0) && ((i % 5) != 0)) || (done == 1);});
            if (done == 0) {
                printNumber(i);
                i++;
            }
            if (i > n) {
                done = 1;
            }
            cv.notify_all();
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
        releaseOxygen();
        sem_post(&semO);
    }
};

// the non-blocking "sem_trywait" solution
class H2O_2 {
public:
    sem_t sem_h;
    sem_t sem_o;
    sem_t sem_c;
    sem_t sem_m;
    H2O_2() {
        sem_init(&sem_h,0,2);
        sem_init(&sem_o,0,1);
        sem_init(&sem_c,0,0);
        sem_init(&sem_m,0,1);
    }

    void hydrogen(function<void()> releaseHydrogen) {
        sem_wait(&sem_h);
        releaseHydrogen();
        if(sem_trywait(&sem_m)!=0) sem_post(&sem_c);
    }

    void oxygen(function<void()> releaseOxygen) {
        sem_wait(&sem_o);
        releaseOxygen();
        //wait until the second hydrogen post sem_c
        sem_wait(&sem_c);
        //post sem_m for the next molecule
        sem_post(&sem_m);
        sem_post(&sem_o);
        sem_post(&sem_h);
        sem_post(&sem_h);
    }
};

class H2O_3 {
public:
    H2O_3() {
        o_cnt = 0;
        h_cnt = 0;
        ready = 0;
        complete = 0;
    }
    std::mutex mtx;
    int o_cnt;
    int h_cnt;
    int ready;
    int complete;
    std::condition_variable cv;
    void hydrogen(function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex>lock(mtx);
        cv.wait(lock, [this](){return (this->h_cnt) < 2;});
        h_cnt++;
        if (h_cnt < 2 || o_cnt < 1) {
            cv.notify_all();
        } else {
            ready=1;
        }

        cv.wait(lock, [this](){return this->ready == 1;});
        releaseHydrogen();
        // only the last atom, who pass the second lock, 
        // can re-init the states
        complete++;
        if(complete == 3) {
            complete = 0;
            ready = 0;
            o_cnt = 0;
            h_cnt = 0;
        }
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        std::unique_lock<std::mutex>lock(mtx);
        cv.wait(lock, [this](){return this->o_cnt < 1;});
        o_cnt++;
        if (h_cnt < 2) {
            cv.notify_all();
        } else {
            ready = 1;
        }

        cv.wait(lock, [this](){return this->ready == 1;});

        releaseOxygen();
        // only the last atom, who pass the second lock, 
        // can re-init the states
        complete++;
        if (complete == 3) {
            complete = 0;
            ready = 0;
            o_cnt = 0;
            h_cnt = 0;
        }
        cv.notify_all(); 
    }
};

// (1226) The Dining Philosophers
class DiningPhilosophers {
    static const int DPC = 5; // Dining Philosopher Count
    std::mutex mtk[DPC]; 
    std::condition_variable cv[DPC];
    int fk[DPC];
    int noble[DPC];
public:
    DiningPhilosophers() {
        for (int i = 0; i < DPC; i++) {
            fk[i] = 1; // 1 means available to use
            if ( (i % 2) == 0 ) {
                noble[i] = 1;
            } else {
                noble[i] = 0;
            }
        }
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int lf_idx = (philosopher + 1) % DPC;
        std::unique_lock<std::mutex>lock_left(mtk[lf_idx]);
        cv[lf_idx].wait(lock_left, [this, lf_idx, philosopher](){
            return (this->fk[lf_idx] == 1) && 
                    (this->noble[philosopher] == 0);});
        fk[lf_idx] = 0;
        pickLeftFork();

        int rf_idx = philosopher;
        std::unique_lock<std::mutex>lock_right(mtk[rf_idx]);
        cv[rf_idx].wait(lock_right, [this, rf_idx](){
            return this->fk[rf_idx] == 1;});
        fk[rf_idx] = 0;
        pickRightFork();

        eat();
        if (noble[(philosopher + DPC - 1) % DPC] == 1) {
            noble[(philosopher + DPC - 1) % DPC] = 0;
            noble[philosopher] = 1;
        }

        putLeftFork();
        fk[lf_idx] = 1;
        cv[lf_idx].notify_all();

        putRightFork();
        fk[rf_idx] = 1;
        cv[rf_idx].notify_all();
		
    }
};
