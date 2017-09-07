#include<stdio.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
if(argc<0)
{
printf("vim 等价于 ");
printf("%s filename,,%d\n",argv[0],argc);//argv[0] 就是执行的时候 dong 这个字符串
return 1;
}
printf("%d\n",argc);
execlp("vim",argv[0],argv[1],NULL);//argv[1]就是用户输入的第二个字符串，也就是文件路径   第一个 就是在PASH环境中找的变量  第二三个就是要的东西
return 0;
}
