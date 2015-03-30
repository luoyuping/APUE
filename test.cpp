#include <stdio.h>
#include <stdlib.h>

void test()
{
    char *p1="hello";
    char *p2="nima!";
    printf("%s %s %s",p1,p2); 
}

int main(int argc, const char *argv[])
{
    //void* p1;
    //int* p2;
    //float* p3;

    //int array[10]={0};

    //p2=array;

    //p1=p2;
    //p3=p1;

    //printf("p1: %x,p2: %x, p3: %x  \n",p1,p2,p3);

    printf("p1: %p,p2: %p, p3: %p  \n",p1,p2,p3);

    return 0;
    test();
}
