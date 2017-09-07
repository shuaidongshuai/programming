#include<stdio.h>
#include<stdlib.h>
void dong(char *a)
{
	if(*a=='*')
	{
	*a='o';
	if(*(a+1)=='*')
	*(a+1)='o';
	else
	*(a+1)='*'; 
}
	else
	{
	*a='*';
	if(*(a+1)=='*')
	*(a+1)='o';
	else
	*(a+1)='*';
}
}
int main()
{
	int i,sum=0;
	char a[100],b[100],*n,*m;
	gets(a);
	gets(b);
	n=a,m=b;
	for(n,m;;n++,m++)
	{
		if(*n=='\0') break;
		else if(*n==*m) continue; 
		else
		{
		dong(n);
		sum++;
	}
	}
	printf("至少要走：%d步",sum);
}
