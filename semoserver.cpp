#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <errno.h>

union semun
{
    int val;
    struct semid_ds* buf;
    ushort   *array;
    struct seminfo* _buf;
    void*  pad;
};



#define   MAX_RESOURCES 5
int main (int argc,char* argv[])
{
    //main ss
    
    key_t key;
    int semid;
    struct sembuf sbuf={0,-1,IPC_NOWAIT};

    union semun semopts;
    // get the key
    if ((key = ftok(".",'s')) <0) { 
        perror("ftok seeror\n");
        exit(-1);
    } 
    if((semid=semget(key,1,IPC_CREAT | 0666)) < 0)
    {
        perror("semget error\n");
    }

    semopts.val = MAX_RESOURCES;
    if(semctl(semid,0,SETVAL,semopts)== -1)
    {
        perror("semctl error \n");
    }
    while(1)
    {
        if(semop (semid,&sbuf,1) == -1)
        {
            perror("semop error!\n");
            exit(1);
        }
        sleep(3);
    }
    return 0;
}
