#include<stdio.h>
int count1=0,count2=0;
int count(int a[],int b,int m,int n)
{
	int i,sum=0;
	for(i=0;i<b;i++)
	{
		if(a[i]==0)
		break;
		if(a[i]==m)
		{
			count1++;
		}
		if(a[i]==n)
		{
			count2++;
		}
		sum+=a[i];
	}
	return sum;
}
int main()
{ 
	int a[40],i,sum=0,m=2,n=6;
	for(i=0;i<40;i++)
	{
	scanf("%d",&a[i]);
	if(a[i]==0)
	break;
}
	sum=count(a,40,m,n);
	printf("2出现%d次",count1);
	printf("6出现%d次",count2);
	printf("总和等于：%d",sum);
}
