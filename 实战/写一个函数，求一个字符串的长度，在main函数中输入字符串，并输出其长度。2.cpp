#include<stdio.h>
int main()
{
	char *p,str[20];
	scanf("%s",&str);
	p=str;
	int n=0;
	while(*p!='\0')
	{
		n++;
		p++;
	}
	printf("一共几个字符：%d",n);
}
