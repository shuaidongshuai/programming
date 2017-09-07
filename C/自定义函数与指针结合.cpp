#include<stdio.h>
void dong(char *a)
{
	*a='2';
}
void dong2(int *a)
{
	*a=1234;
}
int main()
{
	char *a,c;
	int *b,d;
	a=&c;			//同下 
	b=&d;			//这一步不能去掉  指针必须先有一个地址，才能改地址 
	dong(a);
	dong2(b); 
	printf("%c\n%d",*a,*b);
}
