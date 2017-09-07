#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
printf("进程：%ld\n",(long)getpid());
printf("父进程：%ld\n",(long)getppid());
return 0;
}
