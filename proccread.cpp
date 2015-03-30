#include <unistd.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <iostream>

using namespace std;
//const FIFO_NAME   "myfifo"
#define  FIFO_NAME   "myfifo"
//const BUF_SIZE    1024

#define  BUF_SIZE    1024


int main (int argc,char* argv[])
{
    //main ss
    int fd;
    char buff[BUF_SIZE]  ;
    umask(0);

    fd =open(FIFO_NAME,O_RDONLY);
    read(fd,buff,BUF_SIZE);
    cout << buff <<endl;
    close(fd);
    return 0;
}




