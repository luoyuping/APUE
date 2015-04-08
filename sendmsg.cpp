#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h> 
#include <cstdlib> 
#include <iostream> 
#include <cstring> 
#define BUF_SIZE    256
#define PROJ_ID 250 
#define PATH_NAME  "."

using  std::cout;
using  std::endl;

int main (int argc,char* argv[])
{
    //main ss
    struct msgBuf
    {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    }msgbuffer;
    int qid;
    size_t msglen;
    key_t msgkey;

    if((msgkey = ftok(PATH_NAME,PROJ_ID)) == -1)
    {
        cout << "ftok error" << endl;
        exit(-1);
    }
    /*
     * 创建消息队列
     */

    if ((qid = msgget(msgkey,IPC_CREAT |0666)) == -1) { 
        cout <<"create msg queue error or visit queue error"<< endl;
        exit(-1);
    } 

    /*
     * 填充消息结构，发送到消息队列
     */
    msgbuffer.msgtype = 3;
    char msg[20] ="hello message queue";
    strncpy(msgbuffer.ctrlstring,msg,strlen(msg)+1);
    msglen = sizeof(struct msgBuf) -4;
    
    if(msgsnd(qid,&msgbuffer,msglen,0) == -1)
    {
       cout << "msg send error"<<endl;
       exit(-1);
    }    


    return 0;
}




















