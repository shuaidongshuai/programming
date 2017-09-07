#include<stdio.h>
int main()
{
	char str[100];
	// %[^\n] 的意思就是  直到输入回车字符  才结束 
	scanf("%[^\n]",str);//直到输入回车键，读取才结束，当然不能超过a定义的大小，否则会出错。此命令与gets(str)效果一样。
	printf("%s\n",str);
	getchar();			// 用来接收上面的回车键 不然下面会输出回车 
	char str2[100];
	gets(str2);
	puts(str2);
}
