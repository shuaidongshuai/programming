#include<stdio.h>
#include<stdlib.h>
void dong(char a[],int i)
{
	if(a[i]=='*')
	{
	a[i]='o';
	if(a[i+1]=='*')
	a[i+1]='o';
	else
	a[i+1]='*'; 
}
	else
	{
	a[i]='*';
	if(a[i+1]=='*')
	a[i+1]='o';
	else
	a[i+1]='*'; 
}
}
int main()
{
	int i,sum=0;
	char a[100],b[100];
	gets(a);
	gets(b);
	for(i=0;i<100;i++)
	{
		if(a[i]=='\0') break;
		else if(a[i]==b[i]) continue; 
		else
		{
		dong(a,i);
		sum++;
	}
	}
	printf("至少要走：%d步",sum);
}
