#include<stdio.h>
int main()
{
	int i,t,z=-1,a[21];
	for(i=0;i<20;i++)
	{
		a[i]=i;
	}
	printf("请输入一个数：");
	scanf("%d",&t);
	for(i=0;i<20;i++)
	{
		if(t<=a[i]&&(z==-1))
		{
			z=i;
			break;
	}
		a[20]=t;
	 }
	 if(z==-1) a[20]=t;
	else
	{
	 for(i=20;i>z;i--)
	 {
	 	a[i]=a[i-1];
	 }
	 a[z]=t;
}
	 for(i=0;i<21;i++)
	 printf("%-4d",a[i]);
 } 
