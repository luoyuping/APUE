// 练习进程优先级控制的代码
#include <cstdio>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/resource.h> 
#include <sys/wait.h> 
#include <iostream>
using namespace std;

int main (int argc,char* argv[])
{
    pid_t pid;
    int stat_val=0;
    int oldpri,newpri;
    pid = fork();
    switch(pid)
    {
        case 0:
         {    
            printf("child is runnuing \n") ;
            oldpri=getpriority(PRIO_PROCESS,0);
            cout <<oldpri<<endl;
            newpri=nice(2);
            cout <<newpri<<endl;
            _exit(0);

         }
        case -1:
         {
             perror("fork error!\n");
             _exit(-1);
         }
        default:
         {
            printf("parent process is running~\n");
            break;  
         }
    }
    wait(&stat_val);// 父进程等待子进程结束，防止子进程，先于父进程退出后 变成僵死进程
    cout << stat_val<<endl;
    return 0;
}




