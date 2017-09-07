#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

void msg()
{
	while (1)
	{
		MessageBoxA(0, "阿飞有1000个妞", "game", 0);
		Sleep(2000);
	}
}

void main()
{
	int x = 100;
	printf("x地址：%x。。。函数地址：%x\n", &x, msg);
	//msg();//不打开，让外挂tool打开
	while (1)
	{
		printf("阿飞有%d个妞\n", x);
		Sleep(2500);
	}
}