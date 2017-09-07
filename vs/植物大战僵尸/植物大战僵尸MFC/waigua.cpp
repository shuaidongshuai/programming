#include "stdafx.h"

HANDLE hProcess;//进程句柄
BOOL initWaigua(HANDLE *h)
{
	//findwindow  lpClassName参数指向类名，lpWindowName指向窗口名，如果有指定的类名和窗口的名字则表示成功返回一个窗口的句柄。否则返回零。
	HWND hwnd = FindWindow(NULL, TEXT("Plants vs. Zombies 1.2.0.1073 RELEASE"));
	if (NULL == hwnd)
	{
		//AfxMessageBox(TEXT("获取窗口失败"));
		return false;
	}
	//通过窗口获取进程id，也就是PID
	DWORD dwProcessId;
	GetWindowThreadProcessId(hwnd, &dwProcessId);


	//获取进程句柄  1.//渴望得到的访问权限（标志）2. 是否继承句柄  3.进程标示符
	*h = OpenProcess(PROCESS_ALL_ACCESS, NULL, dwProcessId);
	if (!*h)
	{
		AfxMessageBox(TEXT("不能打开进程"));
		return false;
	}
	hProcess = *h;
	return true;
}

//int base = 0x007794f8;
int *get2Point(int base, int p1, int p2)
{
	//ReadProcessMemory  读内存，放到第三个参数中
	int Base,P1, *P2;
	if (!ReadProcessMemory(hProcess, (LPVOID)base,&Base,4,NULL))//返回 Nonzero indicates success.Zero indicatesfailure.
	{
		return NULL;
	}
	if (!ReadProcessMemory(hProcess, (LPVOID)(Base + p1), &P1, 4, NULL))//1.句柄，2.地址，3.装内容的地址，4.大小
	{
		return NULL;
	}
	P2 = (int *)(P1 + p2);
	return P2;
}
int *get3Point(int base, int p1, int p2, int p3)
{
	int Base, P1, P2, *P3;
	if (!ReadProcessMemory(hProcess, (LPVOID)base, &Base, 4, NULL))//返回 Nonzero indicates success.Zero indicatesfailure.
	{
		return NULL;
	}
	if (!ReadProcessMemory(hProcess, (LPVOID)(Base + p1), &P1, 4, NULL))
	{
		return NULL;
	}
	if (!ReadProcessMemory(hProcess, (LPVOID)(P1 + p2), &P2, 4, NULL))
	{
		return NULL;
	}
	P3 = (int *)(P2 + p3);
	return P3;
}

//修改阳光
void modifySun()
{
	int *sun = get2Point(0x007794f8, 0x868, 0x5578);
	int sunValue = 500;
	//返回值 非零值代表成功。
	WriteProcessMemory(hProcess, sun, &sunValue,4,NULL);
}

//修改金钱
void modifyMoney()
{
	int *m = get2Point(0x007794f8, 0x950, 0x50);
	int mValue = 5000;
	WriteProcessMemory(hProcess, m, &mValue, 4, NULL);
}

void modifyPass(int pass)
{
	int *p = get2Point(0x007794f8, 0x950, 0x4C);
	WriteProcessMemory(hProcess, p, &pass, 4, NULL);
}

//修改冷却
void modifyCD()
{
	int	*pCount = get3Point(0x007794f8, 0x868, 0x15c, 0x24);//获取物品栏数
	int *pFirst = get3Point(0x007794f8, 0x868, 0x15c, 0x4c);//植物当前冷却值:  +868 + 15c + 4c
	if (pCount == NULL)
	{
		Sleep(1000);
	}
	int count;
	ReadProcessMemory(hProcess, pCount, &count, 4, NULL);//需要读取物品栏数
	for (int i = 0; i < count; i++)
	{
		if (pFirst == NULL || pFirst + 1 == NULL)
		{
			break;
		}
		//pFirst[0] = pFirst[1];
		int read;
		ReadProcessMemory(hProcess, pFirst + 1, &read, 4, NULL);
		WriteProcessMemory(hProcess, pFirst, &read, 4, NULL);
		pFirst = (int *)((int)pFirst + 0x50);//+868 + 15c + 4c + 50下一个植物
	}
	Sleep(100);
}

//修改暂停
void pauseYes(unsigned char *pCode, unsigned char code[])
{
	DWORD dwOldProtect;
	//修改内存属性	1. 目标地址起始位置  2. 大小  3. 请求的保护方式 4. 保存老的保护方式
	//VirtualProtect(pCode, 3, PAGE_READWRITE, &dwOldProtect);//PAGE_READWRITE 区域可被应用程序读写
	VirtualProtectEx(hProcess, pCode, 3, PAGE_READWRITE, &dwOldProtect);

	//写入retn 4;
	WriteProcessMemory(hProcess, pCode, code, 3, NULL);

	//把属性改回去
	VirtualProtectEx(hProcess,pCode, 3, dwOldProtect, NULL);
}
void pauseNo(unsigned char *pCode, unsigned char code[])
{
	DWORD dwOldProtect;
	//修改内存属性	1. 目标地址起始位置  2. 大小  3. 请求的保护方式 4. 保存老的保护方式
	//VirtualProtect(pCode, 3, PAGE_READWRITE, &dwOldProtect);//PAGE_READWRITE 区域可被应用程序读写
	VirtualProtectEx(hProcess, pCode, 3, PAGE_READWRITE, &dwOldProtect);

	//写入retn 4;
	WriteProcessMemory(hProcess, pCode, code, 3, NULL);

	//把属性改回去
	VirtualProtectEx(hProcess, pCode, 3, dwOldProtect, NULL);
}

