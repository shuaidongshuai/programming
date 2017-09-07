#include<sys/types.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
execl("/mnt/hgfs/linux_program/a.out",argv[0],NULL);
return 0;
}
