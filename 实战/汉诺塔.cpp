#include<stdio.h>
void hano(int n,char a,char b,char c)
{
	if(1==n)
	{
		printf("%c->%c\n",a,c);
	}
	else
	{
		hano(n-1,a,c,b);
		printf("%c->%c\n",a,c);
		hano(n-1,b,a,c);
	}
 } 
 int main()
 {
 	int n; 
 	scanf("%d",&n);
 	hano(n,'A','B','C');
 }
