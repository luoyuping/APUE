#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
using namespace std;

void read_from_pipe(int fd)
{
   char message[100];
   read(fd,message,100);
   cout << "read from the pipe" << endl;
}

void write_to_pipe(int fd)
{
   char message[100];
   write(fd,message,100);
   cout << "write to pipe"<<endl;
}


int main (int argc,char* argv[])
{
    //main ss
    int fd[2];
    pid_t pid;
    if(pipe(fd))
    {
        cout << "create pipe falied" << endl;
    }

    if((pid = fork()) < 0)
    {
        cout << "fork error !" << endl;
    }
    else if (pid == 0)  // child process 
    {
        // 子进程 从管道中fd[0] 读数据
        // 关闭写端
        close(fd[1]);
        read_from_pipe(fd[0]);
        _exit(0);
        
    }
    else   // father process 
    {
        //父进程向管道fd[0]中写数据
       // 关闭读数据端 fd[0]
        close(fd[0]); 
        write_to_pipe(fd[1]);
        _exit(0);
    }
    
    return 0;
}
