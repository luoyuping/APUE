#include "sharememory.h"

int main (int argc,char* argv[])
{
    //main ss
    int semid ,shmid;
    char* shmaddr;

    if((shmid = createshm(".".'m',SHM_SIZE)) ==1)
    {
        exit(-1);
    }

    if((shmaddr = shmat(shmid,(char*)0,0))==(char*)-1)
    {
        cout << "attach shared memory failed" <<endl;
    }

    
    

    return 0;
}
