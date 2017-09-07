#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//首先了解，，exit是c库函数，_exit是系统调用

//打印出   hello world
int main1()
{
	printf("hello world");
	exit(0);
}

//这个函数什么都不会打印，，原因在于 _exit直接转到内核，不进行缓冲区的刷新   而exit要进行缓冲区的刷新，才进入内核
int main2()
{
	printf("hello world");
	_exit(0);
}

//这个函数又能打印出来，，原因在于  /n  有刷新缓冲区的作用
int main3()
{
	printf("hello world\n");
	_exit(0);
}

//fflush(stdout); 这个也是刷新缓冲区用的函数。。但是没有换行
int main()
{
	printf("hello world");
	fflush(stdout);
	_exit(0);
}