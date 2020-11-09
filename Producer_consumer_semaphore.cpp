# include <Windows.h>
# include <stdio.h>
# include <time.h>

HANDLE stuff=CreateSemaphore( NULL ,0 ,5 ,NULL);
HANDLE space=CreateSemaphore( NULL ,5 ,5 ,NULL);
int buf[5];
int top = 0, down = 0;

int main(void)
{
	
    int j, *tid_arg;
	srand((int)time(0)); 
	printf("start\n");
    tid_arg = (int *) malloc(sizeof(int));
    *tid_arg = 1;
	DWORD tid;
	HANDLE Thread[2];
	Thread[0]=CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)producer, (void*)tid_arg, 0, &tid);
	Thread[1]=CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)consumer, (void*)tid_arg, 0, &tid);

	WaitForMultipleObjects(2, Thread, TRUE, INFINITE);              
	system("pause");
    return 0;
}

void * producer(void *arg)
{
	printf("p_in\n");
    int i,tid,in_data;
    tid = *((int *) arg);
    free(arg);
    for (i=0;i<12;i++){
		WaitForSingleObject(space, INFINITE);   //space decrease
		Sleep(rand()%5);
		in_data=rand()%256;
        printf(">>p(%d) =(%d),buf[%d]\n", i, in_data,top);
        buf[top] = in_data;
        top=(top+1)%5;
        ReleaseSemaphore(stuff, 1, NULL);
	}
    return 0;   
}


void * consumer(void *arg)
{
	printf("c_in\n");
    int i,tid,out_data;
    tid = *((int *) arg);
    free(arg);
    for (i=0;i<12;i++){
		WaitForSingleObject(stuff, INFINITE);
		Sleep(rand()%10);
		out_data=buf[down];		
        printf(">>c(%d) =(%d),buf[%d]\n", i, out_data,down);
		down=(down+1)%5;
		ReleaseSemaphore(space, 1, NULL); //space increase
	}
	return 0;  
}

