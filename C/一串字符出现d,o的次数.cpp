#include<stdio.h>
int count1=0,count2=0;
int count(char a[],char b,char c)
{
	int i,sum=0;
	for(i=0;i<40;i++)
	{
		if(a[i]=='b')
		{
			count1++;
		}
		if(a[i]=='c')
		{
			count2++;
		}
	}
}
int main()
{ 
	char a[40],d,o;
    gets(a);
    count(a,d,o);
	printf("d出现%d次",count1);
	printf("o出现%d次",count2);
}
