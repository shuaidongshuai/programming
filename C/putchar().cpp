//c语言函数之一，作用是向终端输出一个字符。其格式为putchar(c)，

//其中c可以是被单引号（英文状态下）引起来的一个字符，

//可以是介于0~127之间的一个十进制整型数（包含0和127），当c为一个介于0~127（包括0及127）之间的十进制整型数时，它会被视为对应字符的ASCII代码，输出该ASCII代码对应的字符；

//也可以是事先用char定义好的一个字符型变量

#include<stdio.h>
int main()
{
	int a=65;
	char *p="hello dong";
	putchar(a);
	putchar('e');
	putchar('dong');	//不能输出字符串 
	return 0;
 } 
