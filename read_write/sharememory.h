// 避免重复包含
#ifndef _SHAREMEMORY_H
#define _SHAREMEMORY
#endif

#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h> 
#include <errno.h>

//创建信号量的函数
int createsem(const char* pathname,int proj_id,int members,int init_val);

// 打开信号量的函数
int opensem(const char* pathname,int proj_id);

// P 操作
int sem_P(int semid,int index);

// V 操作
int sem_V(int semid,int index);

// delete semphore int the kernal
int semdelete(int semid);

// semaphore wait
int sem_wait(int semid,int index);

// 创建共享内存
int create_shm(char* pathname,int proj_id,size_t size);







