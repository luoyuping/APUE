#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>


#define LOOP_TIMES  100

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void critical_section(int  thread_num,int i);

void* thread_worker(void* p)
{
    int i;
    for(i=0; i <LOOP_TIMES; i++)

    {

        pthread_mutex_lock(&mutex2);
        printf("get the mutex2\n");
        pthread_mutex_lock(&mutex1);

        printf("get the mutex1\n");
        critical_section(2,i);


        //pthread_mutex_unlock(&mutex1);
        //pthread_mutex_unlock(&mutex2);

        pthread_mutex_unlock(&mutex1);
        printf("unlock the mutex1\n");

        pthread_mutex_unlock(&mutex2);
        printf("unlock the mutex2\n");
    }


}


void critical_section(int  thread_num,int i)
{
   printf("Thread %d: %d \n",thread_num,i);
}


int main(int argc, const char *argv[])
{
    int i,rtn;

    pthread_t pid = 0;
    rtn = pthread_create(&pid,NULL,thread_worker,NULL);

    if( rtn)
    {
        printf("pthread create failed!");
        return -1;
    }

    for(i =0;i < LOOP_TIMES; i++)
    {

        pthread_mutex_lock(&mutex1);
        printf("get the mutex1\n");

        pthread_mutex_lock(&mutex2);
        printf("get the mutex2\n");

        critical_section(1,i);


        pthread_mutex_unlock(&mutex2);
        printf("unlock the mutex2\n");
        pthread_mutex_unlock(&mutex1);
        printf("unlock the mutex1\n");


    }

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}




