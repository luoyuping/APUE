#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>


#define MAX_THREAD  3

pthread_mutex_t  mutex;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned long long main_counter,counter[MAX_THREAD];

void* thread_work(void* );

int main(int argc, const char *argv[])
{
    int rtn,ch;



    pthread_t  pthread_id[MAX_THREAD] = {0};

    pthread_mutex_init(&mutex,NULL);


    for(int i=0;i < MAX_THREAD; i++)
    {
        pthread_create(&pthread_id[i],NULL, thread_work,(void *)i);

    }

    do{
        unsigned long long sum = 0;
        for (int i=0;i < MAX_THREAD; i++)
        {

            pthread_mutex_lock(&mutex);
            sum += counter[i];

            //pthread_mutex_unlock(&mutex);
            printf("counter %d =   %llu    ",i,counter[i]);

            pthread_mutex_unlock(&mutex);
        }

       // pthread_mutex_lock(&mutex);
        printf("main_counter  %llu ",main_counter);
       // pthread_mutex_unlock(&mutex);

        printf("sum %llu\n",sum);
    } while((ch=getchar())!='q');

    pthread_mutex_destroy(&mutex);
    return 0;
}

void* thread_work(void* p)
{
    int thread_num;

    thread_num = (int)p;
    printf("in thread %lu ,i = %d\n",pthread_self(),thread_num);

    for(;;)
    {
        pthread_mutex_lock(&mutex);
        counter[thread_num]++;


        main_counter ++;
        pthread_mutex_unlock(&mutex);
    }
}












