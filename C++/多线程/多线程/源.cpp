#include<windows.h>
#include<stdlib.h>
DWORD WINAPI mymsg(LPVOID lp)
{
	return MessageBoxA(0, "chen ming dong", "hello", 0);//visual studio 不用加return 
}
void main()
{
	HANDLE hthread;
	DWORD threadid;//保存线程编号
	for (int i = 0; i < 4; i++)
	{
		hthread = CreateThread(
			NULL,//安全属性
			NULL, //堆栈大小
			mymsg,//线程入口
			NULL,//函数参数
			0,//立刻执行
			&threadid);//保存线程id
	}

	system("pause");
}