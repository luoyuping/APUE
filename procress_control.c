#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <stdlib.h>

#define  MAX_CHILD_NUMBER   10

#define SLEEP_INTERVAL  3


int proc_number=0;

void do_something();

int main(int argc, const char *argv[])
{
    int child_proc_number  = MAX_CHILD_NUMBER;
    int i,ch;

    pid_t  child_pid;

    pid_t  pid[10]={10};

    if(argc >1)
    {
       child_proc_number =atoi(argv[1]);

       child_proc_number=(child_proc_number >11)?10 : child_proc_number;
    }


    for (i= 0; i< child_proc_number; i++)
    {
        //proc_number = i;


        child_pid  = fork();
      //  child_pid  = vfork();

        switch(child_pid)
        {

             case -1:
                 {
                     perror("procress creation failed!\n");

                     break;
                 }

            case 0:
                 {
                     proc_number = i;
                    do_something();//把所有子进程陷入死循环状态  方便后面的父进程对子进程的操作
                 }

            default:
            {
                pid[i] = child_pid;
            }

        }
    }


    /*
     * 下面是进程退出的代码
     *
     * 不等于q 时 杀死指定子进程
     */
    while ((ch=getchar())!='q') {
       if( isdigit(ch))
       {

          printf("child %d exited\n",pid[ch-'0']);
          kill(pid[ch-'0'], SIGTERM);
         //_exit(0);

       }
    }


    /*
     * 这是默认等于 q
     * 所以 退出所有进程
     */

    for (i=0; i < child_proc_number; i++)
    {

        printf("child procress %d exiting\n",pid[i] );
        kill (pid[i],SIGTERM);
    }

    return 0;

}

void   do_something()
{
     while(1)
    {
        printf("this is procress No.%d and its pid is %d \n\n",proc_number,getpid());
        sleep(SLEEP_INTERVAL);
    }
}















