// thread waiting for multiple event to happen

#include <semaphore.h>
// the mutex solution
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
