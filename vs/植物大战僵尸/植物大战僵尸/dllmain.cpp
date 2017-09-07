// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <thread>

//基址上存的是b对象的地址，b对象的地址 加上868上是a对象的地址
//	 b			a		   sum
//	 &b   868   &a	5578   &sum
//	基址

//int base = 0x007794f8;
int *get2Point(int base, int p1, int p2)
{
	//BOOL IsBadReadPtr(CONST VOID *lp,UINT_PTR ucb); 函数:检查进程是否有权限访问指定的内存块  如果调用进程有权限访问该内存，返回0 
	int P1, P2;
	if (IsBadReadPtr((LPVOID)base, 4))//我们需要判断，这片内存可不可读。因为一局完了以后，内存会变
	{
		return NULL;
	}
	P1 = *(int*)base;//这里的b代表了 b的地址	为了不用在右边取地址符了，太复杂了，反正我们利用的只是他们的地址，不需要对象。
	if (IsBadReadPtr((LPVOID)(P1 + p1), 4))
	{
		return NULL;
	}
	P2 = *(int *)(P1 + p1);// a也一样
	if (IsBadReadPtr((LPVOID)(P2 + p2), 4))
	{
		return NULL;
	}
	int *res = (int *)(P2 + p2);//res 没有抽象，我们只需要最后一层的对象，来修改他的值
	if (IsBadWritePtr((LPVOID)res, 4))//对于要操作的地址我们要检查是否可写
	{
		return NULL;
	}
	return res;
}
int *get3Point(int base, int p1, int p2,int p3)
{
	int P1, P2, P3;
	if (IsBadReadPtr((LPVOID)base, 4))
	{
		return NULL;
	}
	P1 = *(int*)base;
	if (IsBadReadPtr((LPVOID)(P1 + p1), 4))
	{
		return NULL;
	}
	P2 = *(int *)(P1 + p1);
	if (IsBadReadPtr((LPVOID)(P2 + p2), 4))
	{
		return NULL;
	}
	P3 = *(int *)(P2 + p2);
	if (IsBadReadPtr((LPVOID)(P3 + p3), 4))
	{
		return NULL;
	}
	int *res = (int *)(P3 + p3);
	if (IsBadWritePtr((LPVOID)res, 4))//对于要操作的地址我们要检查是否可写
	{
		return NULL;
	}
	return res;
}

//修改阳光
void modifySun()
{
	int *sun = get2Point(0x007794f8, 0x868, 0x5578);
	if (sun)
		*sun = 5000;

}
//修改金钱
void modifyMoney()
{
	int *m = get2Point(0x007794f8, 0x950, 0x50);
	if (m)
		*m = 50000;
}

//第一个参数是指向SECURITY_ATTRIBUTES型态的结构的指针。在Windows 98中忽略该参数。在Windows NT中，它被设为NULL。
//第二个参数是用于新线程的初始堆栈大小，默认值为0。在任何情况下，Windows根据需要动态延长堆栈的大小。
//第三个参数是指向线程函数的指标。函数名称没有限制，但是必须以下列形式声明：
//DWORD WINAPI ThreadProc(PVOID pParam);
//第四个参数为传递给ThreadProc的参数。这样主线程和从属线程就可以共享数据。
//第五个参数通常为0，但当建立的线程不马上执行时为旗标CREATE_SUSPENDED。线程将暂停直到呼叫ResumeThread来恢复线程的执行为止。
//第六个参数是一个指标，指向接受执行绪ID值的变量。
DWORD WINAPI run(
	LPVOID lpThreadParameter
	)
{
	while (1)
	{
		modifySun();//由于要玩几次，每次我们都应该修改金钱值

		int	*pCount = get3Point(0x007794f8, 0x868, 0x15c, 0x24);//获取物品栏数
		int *pFirst = get3Point(0x007794f8, 0x868, 0x15c, 0x4c);//植物当前冷却值:  +868 + 15c + 4c
		if (pCount == NULL)
		{
			Sleep(1000);
			continue;
		}
		for (int i = 0; i < *pCount; i++)
		{
			if (pFirst == NULL || pFirst + 1 == NULL)
			{
				break;
			}
			pFirst[0] = pFirst[1];//令当前冷却值=冷却时间(达到冷却时间才能又放植物)   植物冷却时间 : +868 + 15c + 50
			pFirst = (int *)((int)pFirst + 0x50);//+868 + 15c + 4c + 50下一个植物
		}
		Sleep(200);
	}
}

//修改冷却
void modifyCD()
{
	CreateThread(0, 0, run, 0, 0, 0);
}

//修改暂停
void modifyPause()
{
	unsigned char *pCode = (unsigned char*)0x00472B50;//要写入的地址
	DWORD dwOldProtect;
	//修改内存属性	1. 目标地址起始位置  2. 大小  3. 请求的保护方式 4. 保存老的保护方式
	VirtualProtect(pCode, 3, PAGE_READWRITE,&dwOldProtect);//PAGE_READWRITE 区域可被应用程序读写

	//00472B50 retn 4 机器码 C2 0400	我们需要在函数开头的地方就，直接return 不进行暂停操作
	//00472B50 原来的 机器码 55 88EC
	pCode[0] = 0xC2;
	pCode[1] = 0x04;
	pCode[2] = 0x00;
	//把属性改回去
	VirtualProtect(pCode, 3, dwOldProtect, NULL);
}

void modifyPass()
{
	int *p = get2Point(0x007794f8, 0x950, 0x4C);
	if (p)
		*p = 36;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		modifyCD();
		modifyPause();
		modifyPass();
		modifyMoney();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

