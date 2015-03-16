#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>


#define MAX_THREAD  3

unsigned long long main_counter,counter[MAX_THREAD];

void* thread_work(void* );

int main(int argc, const char *argv[])
{
    int rtn,cn;

    pthread_t  pthread_id[MAX_THREAD] = {0};
    for(int i=0;i < MAX_THREAD; i++)
    {
        pthread_create(&pthread_id[i],NULL, thread_work,(void *)i);

    }

    do{
        unsigned long long sum = 0;
        for (int i=0;i < MAX_THREAD; i++)
        {
            sum += counter[i];
            printf("counter %d =   %llu    ",i,counter[i]);
        }

        printf("main_counter  %llu ,sum %llu\n",main_counter,sum);
    } while((cn=getchar())!='q');

    return 0;
}

void* thread_work(void* p)
{
    int thread_num;

    thread_num = (int)p;
    printf("in thread %lu ,i = %d\n",pthread_self(),thread_num);

    for(;;)
    {
        counter[thread_num]++;
        main_counter ++;
    }
}












