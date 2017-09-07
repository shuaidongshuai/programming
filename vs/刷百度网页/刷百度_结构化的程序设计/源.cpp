#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void openbaidu()
{
	ShellExecuteA(0, "open", "http://blog.csdn.net/program_anywhere", 0, 0, 2);//打开网页
}

void close()
{
	system("taskkill /f /im chrome.exe");
}

void clickbaidu()
{
	SetCursorPos(490, 507);

	Sleep(50);

	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//模拟鼠标按下
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//模拟鼠标弹起

	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void main()
{
	
	while (1)
	{
		openbaidu();
		Sleep(5000);
		clickbaidu();
		Sleep(5000);
		close();
		Sleep(5000);
	}

}