#include<stdio.h>
void change(int b)
{
	if(b!=0)
	{
	int a;
	a=b%16;
	b/=16;
	change(b);
	if(0<=a<16)
	{
		if(a<10)
		printf("%d",a);
		else if(a<16)
		printf("%c",a-10+'A');
	}
}
}
int main()
{
	int a;
	scanf("%d",&a);
	if(a!=0)
	change(a);
	else
	printf("0");
	return 0;
 } 
