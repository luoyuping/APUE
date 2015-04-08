#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h> 
#include <cstdio>
#include <cstdlib> 
#include <errno.h>

#define   MAX_RESOURCES 5
int main (int argc,char* argv[])
{
    //main ss
    
    key_t key;
    int semid;
    int semval;
    //struct sembuf sbuf={0,-1,IPC_NOWAIT};

    //union semun semopts;
    // get the key
    if ((key = ftok(".",'s')) <0) { 
        perror("ftok seeror\n");
        exit(-1);
    } 
    if((semid=semget(key,1,IPC_CREAT | 0666)) < 0)
    {
        perror("semget error\n");
    }

    while(1)
    {
        if((semval = semctl(semid,0,GETVAL,0))== -1)
        {
            perror("sermctl error\n");
        }
        if(semval > 0)
        {
            printf("still %d res left \n",semval);
        }
        else
        {
            printf("no res left \n");
            break;
        }
        sleep(3);
    }
    return 0;
}

