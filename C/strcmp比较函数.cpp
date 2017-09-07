#include<stdio.h>
#include<string.h>
int main()
{
	int a;
	char str1[100],str2[100];
	scanf("%s%s",str1,str2);
	a=strcmp(str1,str2);
	printf("a=%d\n",a);// 先比较第一个数  如果第一个数==第二个数  就继续比较   如果不等于0   就用str1[i]-str2[i] 的 字符ASCII码  相减==多少 这就是返回值 
}
