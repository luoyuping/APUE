#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int glob = 0;


int main(int argc, const char *argv[])
{
    int var =0;

    pid_t pid ;
    if(( pid =fork()) >0)
    {
        var += 10;
        glob +=10;
        sleep(2);
    }
    else if(pid == 0) {
        var += 20;
        glob +=20;

        sleep(2);
    }
    else {
        perror("fork error\n");
    }


    printf("in procress %d ,var = %d, glob = %d \n\n",getpid(),var,glob);



    return 0;
}
