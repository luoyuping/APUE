// 通过pipe 调用 /bin/more  实现将一个文本文件分页显示输出
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring> 
using namespace std;

#ifndef  def_pager
#define def_pager "/bin/more"
#endif
#define err_quit(message) \
    do { \
        cout << message << endl; \
        exit(1); \
    } while(0)

#define MAX 20

int main (int argc,char* argv[])
{
    //main ss
    int fd[2];
    int fp;
    char buff[MAX];

    if(argc != 2)
    {
        err_quit("参数错误,usage : pipe_more <file pathname>");
    }    
    if((fp =open(argv[1],O_RDONLY)) < 0)
    {
        err_quit("can not open the file");
    }

    if(pipe(fd) < 0)
        err_quit("create pipe error");
   //
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        err_quit("fork error");
    }   
    else if(pid > 0)
    {
        close(fd[0]); // 关闭 读端
        
        // 把agrv[1] 文件拷贝到 管道写端
        while(read(fp,buff,MAX) > -1)
        {
            write(fd[1],buff,sizeof(buff)/sizeof(buff[0]));
        }
        close(fd[1]);
        waitpid(pid,NULL,0);
        exit(0);
    }
    else
    {
        close(fd[1]); // close the write port 
        if(fd[0] != STDIN_FILENO) // 把读端的文件描述符，拷贝到标准读 stdin
        {
            if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO)
            {
                err_quit("can not dup to stdin!");
            } 
            close(fd[0]); // do not need this any more
        }
        char * pager;
        char * argv0;
        if((pager = getenv("PAFER"))==NULL)
        { 
            pager =( char *) def_pager;
        }
        if((argv0 = strrchr(pager,'/')) !=NULL)
            argv0++;
        else
            argv0=pager;
        if(execl(pager,argv0,(char*)0) < 0)
            err_quit("execute error");
    }
    return 0;
}











