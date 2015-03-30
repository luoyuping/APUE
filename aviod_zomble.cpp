#include <cstdio> 
#include <unistd.h> 
#include <cstdlib> 
#include <sys/types.h> 
#include <sys/wait.h> 


// 下面这种fork的布局，父子进程完全脱离，即没有重复使用的代码 
int main (int argc,char* argv[])
{
    pid_t pid1,pid2;
    pid1=fork();
    if(pid1 == 0)
    {
        pid2=fork();
        if(pid2 ==0)
        {
            // to do what you need to do in the grand process
            sleep(10);
            _exit(0);
        }
        else
        {
            // 让子进程 退出
            _exit(0);
        }
    } 
    else
    {
        // 父进程立即阻塞
        wait(NULL);
        printf("the first process");

    }
    return 0;
}




