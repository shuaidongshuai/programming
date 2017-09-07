#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void openbaidu()
{
	ShellExecuteA(0, "open", "http://blog.csdn.net/program_anywhere", 0, 0, 3);
}

void close()
{
	system("taskkill /f /im chrome.exe");
}

void clickbaidu()
{
	SetCursorPos(30, 30);

	Sleep(50);

	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void main()
{
	clickbaidu();
	/*while (1)
	{
	openbaidu();
	Sleep(5000);
	close();
	Sleep(5000);
	}*/
	

	//getchar();
}