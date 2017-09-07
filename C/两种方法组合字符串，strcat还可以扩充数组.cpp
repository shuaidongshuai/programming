#include<stdio.h>
#include<string.h>
int main()
{
	char a[]="123";
	char p[9]="/dev/led";
	strcat(p,a);
	printf("%s",p);
	
	printf("\n%c\n",p[10]);//突然发现strcat 还可以扩充字符数组大小  本身p[]数组是没有 p[10]的 
	
	int b = 321; 
	char q[20];
	sprintf(q,"/dev/led%d",b);//sprintf比strcat强大，，它还可以把 数字 和 字符串 合并 
	printf("%s\n",q);
	
	int c = 123;
	char d[30];
	sprintf(d,"321    \n    %d",c);//这样的字符串 带空客 带回车的  都可以一起转化为一个 字符数组     所以sprintf非常强大 
	printf("%s",d);
 } 
