#include <unistd.h>
#include <pthread.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <cstdlib> 
#include <iostream> 
using namespace std;

typedef struct _port_segment
{
    struct in_addr  dest_ip;
    // 定义扫描的起始窗口和终止窗口
    unsigned short int  start_port;   
    unsigned short int  end_port;

} port_segment;

void my_error(const char* error_string,int line)
{
   fprintf(stderr,"line:%d",line);
   perror(error_string);
   //exit(1);
}

/*
 * 扫描某一ip地址上的开放某一端口的函数
 *-1:出错
 * 0:目标端口未打开
 *1:目标端口已经打开
*/
int do_scan(struct sockaddr_in serv_addr)
{
    int conn_fd;
    int ret;

    // create a socket
    conn_fd = socket(AF_INET,SOCK_STREAM,0);
    if(conn_fd < 0)
    {
        my_error("socket",__LINE__);
    }
    if((ret = connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))) < 0)
    {
        // the task port unopen
        //if(errno == ECONNREFUSED)
        //{
            //close(conn_fd);
            //return 0;
        //}
        //// other mistake
        //else
        //{
            //close (conn_fd);
            //return -1;
        //}
       close (conn_fd);
       return -1;

    }
    else if(ret == 0)     // connect succ
    {
        cout << "port"<<ntohs(serv_addr.sin_port)<<" was found in " << inet_ntoa(serv_addr.sin_addr) << endl;
        close(conn_fd);
        return 0;
    }
    return -1;
}

// 执行扫描端口的线程
void*  scaner(void* arg)
{
    //unsigned short int i;
    struct sockaddr_in serv_addr;
    port_segment portinfo;

    memcpy(&portinfo,arg,sizeof(port_segment));
    // 
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = portinfo.dest_ip.s_addr;
    for(unsigned short int i =portinfo.start_port;i < portinfo.end_port; i++)
    {
        serv_addr.sin_port = htons(i);
        if(do_scan(serv_addr) < 0)
        {
            continue;
        }
    }
    return NULL;
}

int main (int argc,char* argv[])
{
    //main ss
    
    pthread_t*  thread;
    int max_port;
    int thread_num;
    int seg_len;
    struct in_addr dest_ip;
    //int i;
    bool flag= false;

    while( flag == false)
    {
        if(argc != 7)
        {
            cout << "usage : -m  maxport -a servaddr -n thread_num" << endl<< "try_again:";
            flag = true;
            continue;
        }
        flag = true;
    }

    // 解析命令行参数
    
    for(int i =0; i < argc; i++)
    {
        if(strcmp("-m",argv[i])==0)
        {
            max_port= atoi(argv[i+1]);
            if(max_port < 0 | max_port > 65535)
            {
                my_error("wrong port",__LINE__);
                exit(1);
            }
            continue;
        }
        if(strcmp("-a",argv[i])== 0)
        {
            if(inet_aton(argv[i+1],&dest_ip) ==0)
            {
                cout << "invalid ip address" << endl;
                exit(1);
            }
            continue;
        }
        if(strcmp("-n",argv[i]) == 0)
        {
            thread_num = atoi(argv[i+1]);
            if(thread_num <= 0)
            {
                cout << "invalid number" << endl;
            }
            continue;
        }
    }


    if(max_port < thread_num)
    {
        thread_num =max_port;
    }

    seg_len = max_port/thread_num;
    if((max_port % thread_num )!=0)
    {
        thread_num +=1;
    }

    thread =(pthread_t*)malloc(thread_num * sizeof(pthread_t));

    for(int i =0; i < thread_num ;i ++)
    {
        port_segment portnum;
        portnum.dest_ip = dest_ip;
        portnum.start_port =(unsigned int) i*seg_len +1;
        if(i == thread_num -1 )
        {
            portnum.end_port = (unsigned int) max_port;
        }
        else
        {
            portnum.end_port = portnum.start_port + seg_len -1;
        }

        if(pthread_create(&thread[i],NULL,scaner,(void*)&portnum))
        {
            my_error("pthread_create",__LINE__);
            exit(1);
        }
    // main thread wait the child thread ends
    
        pthread_join(thread[i],NULL);
     }
    return 0;

}




























































