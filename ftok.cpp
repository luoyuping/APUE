#include <sys/types.h>
#include <sys/ipc.h>
#include <cstdio>
#include <cstdlib>


int main (int argc,char* argv[])
{
    //main ss
    key_t msgkey;
    for (int i = 0; i < 5; ++i) { 
     msgkey = ftok("..",i);
     if(msgkey < 0)
     {
         printf("generate ipc key failed,error key is %d \n",msgkey);
     }
    } 
    return 0;
}





