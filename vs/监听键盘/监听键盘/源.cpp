#include<Windows.h>

void key()
{
	keybd_event(VK_LWIN, 0, 0, 0);//键盘按下
	keybd_event(VK_LWIN, 0, 2, 0);//键盘松开
}
void zuhe1()
{
	//组合键
	keybd_event(VK_LWIN, 0, 0, 0);//键盘按下
	keybd_event('E', 0, 0, 0);//E键按下
	keybd_event('E', 0, 2, 0);//E键松开
	keybd_event(VK_LWIN, 0, 2, 0);//键盘松开
}
void zuhe2()
{
	//组合键
	keybd_event(VK_LWIN, 0, 0, 0);//键盘按下
	keybd_event('R', 0, 0, 0);//R键按下
	keybd_event('R', 0, 2, 0);//R键松开
	keybd_event(VK_LWIN, 0, 2, 0);//键盘松开
}
void zuhe3()
{
	//组合键
	keybd_event(VK_LWIN, 0, 0, 0);//键盘按下
	keybd_event('R', 0, 0, 0);//R键按下
	keybd_event('R', 0, 2, 0);//R键松开
	keybd_event(VK_LWIN, 0, 2, 0);//键盘松开

	Sleep(1000);

	keybd_event('C', 0, 0, 0);
	keybd_event('C', 0, 2, 0);
	keybd_event('A', 0, 0, 0);
	keybd_event('A', 0, 2, 0);
	keybd_event('L', 0, 0, 0);
	keybd_event('L', 0, 2, 0);
	keybd_event('C', 0, 0, 0);
	keybd_event('C', 0, 2, 0);
	keybd_event(VK_RETURN, 0, 0, 0);//回车键
	keybd_event(VK_RETURN, 0, 2, 0);
}

void main()
{
	zuhe3();
	Sleep(5000);
	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(VK_F4, 0, 0, 0);
	keybd_event(VK_F4, 0, 2, 0);
	keybd_event(VK_MENU, 0, 2, 0);
}