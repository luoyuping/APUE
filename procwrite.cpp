#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <iostream>
using namespace std;
#define    FIFO_NAME  "myfifo"
#define    BUF_SIZE    1024

int main (int argc,char* argv[])
{
    int fd;
    //char buff[BUF_SIZE] ="hello proc read, i come from procwrite";
    string s("hello proc read, i come from procwrite");

    umask(0);
    if(mkfifo (FIFO_NAME,S_IFIFO | 0666)==-1)
    {
        //perror("fopen error");
        cout << "create namedpipe error"<<endl;
        exit(1);
    }

    if((fd=open(FIFO_NAME,O_WRONLY)==-1))
    {
        //perror("open error!");
        cout << "open named pipe error" << endl;
        exit(-1);
    }

    write(fd,string::iterator i=s.begin(),s.length() +1);// needto pass iterator
    
    return 0;
}







