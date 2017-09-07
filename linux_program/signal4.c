#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
/*自定义信号处理函数*/
void my_func(int sign_no)
{
    if(sign_no==SIGINT)
        printf("I have get SIGINT\n");
    else if(sign_no==SIGQUIT)
        printf("I have get SIGQUIT\n");
}
int main()
{
    printf("Waiting for signal SIGINT or SIGQUIT \n ");
    /*发出相应的信号，并跳转到信号处理函数处*/
    signal(SIGINT, my_func);
    signal(SIGQUIT, my_func);
	
    pause();
    exit(0);
}
// 执行 ./signal，执行结果如下：
// Waiting for signal SIGINT or SIGQUIT
// I have get SIGINT       /*按下Ctrl+C,操作系统就会向进程发送SIGINT信号*/
// I have get SIGQUIT      /*按下Ctrl+\（退出）,操作系统就会向进程发送SIGQUIT信号*/

