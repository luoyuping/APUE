#include <sys/time.h>
#include <sys/types.h> 
#include <unistd.h>
#include <time.h> 
#include <cstdio>
#include <cstdlib> 
void display_time(const char* str)
{
    int seconds;
    seconds = time((time_t*)NULL);
    printf("%s,%d\n",str,seconds);

}


int main (int argc,char* argv[])
{
    //main ss
    fd_set  readfds;
    struct timeval timeout;
    int ret;

    /* 监视标准输入是否有数据输入
     *
     */

    FD_ZERO(&readfds);
    FD_SET(0,&readfds);

    while(1)
    {
        /*
         * 设置阻塞时间
         */
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        display_time("before select");
        ret = select(1,&readfds,NULL,NULL,&timeout);
        display_time("after select");
        switch(ret)
        {
            case 0:
                printf("no date in 10 secds\n");
                exit(0);
                break;
            case -1:
                perror("select");
                exit(1);
                break;
            default:
                {
                    getchar();  //  将数据从输入缓冲区都出来
                 
                    printf("date is available now\n");
                }
        }
    }        
    return 0;
}








