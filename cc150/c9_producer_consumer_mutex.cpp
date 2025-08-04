//Given set of N threads generate sum of all numbers in an array of known size M

# include <stdio.h>
# include <stdlib.h>
# include <thread>
# include <mutex>
# include <condition_variable>
# define BufferSize 10
static const unsigned int n = 25;
int head = 0, tail = 0;
char *BUFFER;

void Producer(int n);
void Consumer(int n);
std::mutex mtx;
std::condition_variable cv;
int main()
{
    BUFFER=(char *) malloc(sizeof(char) * BufferSize);

    std::thread thd_cons(Consumer, n);
    std::thread thd_prod(Producer, n);

    thd_prod.join();
    thd_cons.join();

    free(BUFFER);

    return 0;
}
void Producer(int n)
{
    for(int i = 0; i < n; i++)
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [](){return ((head + 1) % BufferSize) != tail;});
            BUFFER[head] = rand() % 256;
            printf("Produce : %d at %d\n", BUFFER[head], head);
            head = (head + 1) % BufferSize;
        }
        sleep(1);
        cv.notify_one();
    }

}

void Consumer(int n)
{
    for(int i = 0; i < n; i++)
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [](){return head != tail;});
            printf("Consume : %d at %d \n", BUFFER[tail], tail);
            BUFFER[tail] = '$';
            tail = (tail + 1) % BufferSize;
        }
        cv.notify_one();
    }
}
