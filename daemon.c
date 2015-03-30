#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

int init_daemon(void)
{
   int pid;
   int i;
   signal(SIGTTOU,SIG_IGN);
   signal(SIGTTIN,SIG_IGN);
   signal(SIGTSTP,SIG_IGN);
   signal(SIGHUP,SIG_IGN);

   pid=fork();
   if(pid > 0)
   {
     exit(0);
   }
   else if(pid < 0)
   {
      return -1;
   }  

   setsid();
   pid=fork();
   if(pid > 0)
   {
      exit(0); 
   }     
   else if(pid < 0)
   {
       return -1;
   }
   /* 关闭所有从父进程继承的不再需要的文件描述符*/
   for (int i = 0;  i < NOFILE; ++ i)
   {
       close(i);
   }
   chdir("/");// 改变工作目录，使得进程不在与任何文件系统联系
   umask(0);  // 将文件的屏蔽字设置为零
   signal(SIGCHLD,SIG_IGN) ;
   return 0;
}

int main(int argc, char *argv[])
{
    time_t now;
    init_daemon();
    syslog(LOG_USER | LOG_INFO,"测试守护进程/n");
    while(1)
    {
       sleep(8);
       time(&now);
       syslog(LOG_USER | LOG_INFO,"系统时间\t%s\t\t\n",ctime(&now));
    }

    return 0;
}







