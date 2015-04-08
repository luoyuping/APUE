#include "sharememory.h"
#include <iostream>

using namespace std;


int create_shm(const char* path,int proj_id,int numbers,int init_val)
{
    key_t  msgkey;
    int index,sid;
    union semun semopts;
    if((msgkey = ftok(path,proj_id)) == -1)
    {
        cout << "ftok error" << endl;
        exit(-1);
    }

    if((sid=semget(msgkey,numbers,IPC_CREAT |0666 )) ==-1)
    {
        cout << "semget errror" << endl;
        exit(-1);
    }

    /*
     * 初始化操作
     */
    semopts.val = init_val; // ?
    for(index = 0; index < numbers ; index ++)
    {
        semctl(sid,index,SETVAL,semopts);
    }
    return sid;
}

int opensem(const char* pathname,int proj_id)
{
    key_t key;
    int sid;
    if((msgkey = ftok(pathname,proj_id)) == -1)
    {
        cout << "ftok error" << endl;
        exit(-1);
    }
    if((semget(key,0,IPC_CREAT | 0666)) == -1)
    {
        cout << "semget error" << endl;
        exit(-1);
    }

    return sid;
}

int sem_P(int semid,int index)
{
    struct sembuf buf = {0,-1,IPC_NOWAIT};
    if(index < 0)
    {
        cout << "index error" << endl;
        exit(-1);
    }

    buf.sem_num = index;
    if(semop(semid,&buf,1) == -1)
    {
        cout << "senmop error" << endl;
        exit(-1);
    }
    return 0;
}

int sem_V(int semid,int index)
{
    struct sembuf buf = {0,1,IPC_NOWAIT};
    if(index < 0)
    {
        cout << "index error" << endl;
        exit(-1);
    }

    buf.sem_num = index;
    if(semop(semid,&buf,1) == -1)
    {
        cout << "senmop error" << endl;
        exit(-1);
    }
    return 0;
}

int semdelete(int semid)
{
    return (semctl(semid,0,IPCRMID));
}


int wait_sem(int semid,int index)
{
    while(semctl(semid,index,GETVAL) < 0)
    {
      sleep(1);
    }
    return 1;
}


int createshm(char* pathname,int proj_id,size_t size)
{
    key_t key;
    int sid;

   // 获取键值
   if((key=ftok(pathname,proj_id)) == -1)
   {
      cout << "ftok error" << endl;
      exit(-1);
   }

  if((sid= shmget(key,size,IPC_CREAT | 0666)) ==-1)
  { 
      cout << "shmget error" <<endl;
      exit(-1);
  }
  return sid;
}


    



     












