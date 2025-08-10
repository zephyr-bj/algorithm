#include <stdio.h>
#include <time.h>
#include <semaphore>
#include <thread>
//just want to try git push
static const int sz = 5;
static const int n = 12;
std::counting_semaphore<sz> sem_stuff(0);
std::counting_semaphore<sz> sem_space(sz);
int buf[sz];
int head = 0, tail = 0;

void producer(int n);
void consumer(int n);
int main(void)
{
    srand((int)time(0));
    printf("start\n");
    std::thread thd_producer(producer, n);
    std::thread thd_consumer(consumer, n);

    thd_consumer.join();
    thd_producer.join();
    printf("done\n");
    return 0;
}

void producer(int n)
{
    printf("p_in\n");
    int i, in_data;
    for (i = 0; i < n; i++){
        sem_space.acquire();
         sleep(rand()%5);
        in_data = rand()%256;
        printf(">>p(%d) =(%d),buf[%d]\n", i, in_data, head);
        buf[head] = in_data;
        head = (head + 1) % sz;
        sem_stuff.release();
    }
}

void consumer(int n)
{
    printf("c_in\n");
    int i,out_data;
    for (i = 0; i < n; i++){
        sem_stuff.acquire();
        sleep(rand()%10);
        out_data=buf[tail];
        printf(">>c(%d) =(%d),buf[%d]\n", i, out_data, tail);
        tail = (tail + 1) % sz;
        sem_space.release();
    }
}

                                                                                                         1,1           Top
