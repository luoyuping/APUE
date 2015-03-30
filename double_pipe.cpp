#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <sys/wait.h> 
using namespace std;


// 管道读写的顺序不要搞错，是先写再读，一读一写，可能会造成死锁
// 两者都先读后写，一定造成死锁

void
child_rw_pipe(int  fd_r,int  fd_w)
{
    char* message_send =(char*) "the message is from the child";
    char message_recv[100];
    cout <<"i will read first from the pipe" <<endl;
    ssize_t count1= read(fd_r,message_recv,100);
    cout << message_recv <<endl<<"totally "<<count1<<"chars" <<endl;
    cout << "fine ,i have recv from the pipe,now i can send to the aprent process" << endl;
    ssize_t count2=write(fd_w,message_send,strlen(message_send)+1);
    //ssize_t count2=write(fd_w,message_send,strlen(message_send));
    cout << "send "<<count2<<"char2"<<endl;
}

void
parent_rw_pipe(int fd_r,int fd_w)
{
    
    char* message_send =(char*) "the message is from the parent";
    char message_recv[100];

    //read(fd_r,message_recv,100);
    //cout << message_recv <<endl;
    //write(fd_w,message_send,strlen(message_send)+1);
    ssize_t count2=write(fd_w,message_send,strlen(message_send)+1);
    //ssize_t count2=write(fd_w,message_send,strlen(message_send));
    cout << "send "<<count2<<"char2"<<endl;

    ssize_t count1= read(fd_r,message_recv,100);
    cout << message_recv <<endl<<"totally "<<count1<<"chars" <<endl;
}

int main (int argc,char* argv[])
{
    //main ss
    int pipe1[2],pipe2[2];
    pid_t pid;
    //int stat_val;

    //创建俩个管道,组建双管道通讯,成功返回零
    if(pipe(pipe1))
    {
        cout << "create pipe1 failed " << endl;
    }
    
    if(pipe(pipe2))
    {
        cout << "create pipe2 failed " << endl;
    }

    // create the child process
    pid = fork();
    switch(pid)
    {
        case -1:
            {
                cout << "fork error"<<endl;
                break;
            }
        case 0:
            {
                close(pipe1[1]); // read the date from the pipe1;
                close(pipe2[0]); // write the date into the pipe2;
                // call the fun
                child_rw_pipe (pipe1[0],pipe2[1]);
                break;
            }
        default:
            {
               close(pipe1[0]);// write the date from the pipe1;
               close(pipe2[1]); // read the date into the pipe;
               parent_rw_pipe (pipe2[0],pipe1[1]);

               //wait(&stat_val);
            }
    }
    return 0;
}










