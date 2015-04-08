#include "sharememory.h"

int main (int argc,char* argv[])
{
    //main ss
    int semid,shmid;
    char *shmaddr;
    char write_str[SHM_SIZE];
    memset(write_str,SHM_SIZE,'\0'); 
    if ((shmid = createshm(".",'m',SHM_SIZE)) == -1) { 
        exit(-1);
    } 

    if((shmaddr = shmat(shmid,(char*)0,0)) == (char*)-1)
    {
        cout << "shmat error" << endl;
    }
   if((semid =(createsem(".",'s',1,1)))==-1)
   {
       exit(-1);
   }

   while(1)
   {
       wait_sem(semid,0);
       sem_P(semid,0);
       cout << "writer:"<< "do something here" << endl;
       fgets(write_str,1024,stdin);
       int length = strlen(write_str);
       write_str[len]='\0';
       strncpy(shmaddr,write_str,len+1);
       sleep(10);
   }
    return 0;
}
