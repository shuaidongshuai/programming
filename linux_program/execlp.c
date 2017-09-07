#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
execlp("/bin/ls","ls","-l",NULL);//1也就是文件路径 ls和以后的东西都是要执行的步骤  等价于 执行 ls -al 
return 0;
}
