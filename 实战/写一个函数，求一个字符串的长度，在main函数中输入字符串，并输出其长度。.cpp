#include<stdio.h>
int lens(char *p)
{
	int n=0;
	while(*p!='\0')
	{
		n++;
		p++;
		printf("%c\n",*(p+6-n));
		return n;
}
}
int main()
{
	char str[20];
	scanf("%s",str);
	int len;
	len=lens(str);
	printf("一共几个字符：%d",len);
}
