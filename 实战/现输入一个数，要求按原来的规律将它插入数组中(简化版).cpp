#include<stdio.h>
int main()
{
	int i,j,t,z=-1,a[21];
	for(i=0;i<20;i++)
	{
		a[i]=i;
	}
	printf("请输入一个数：");
	scanf("%d",&t);
	if(t>=a[19]) a[20]=t;
	else
	{
	for(j=0;j<20;j++)
	{
		if(t<a[j]&&z==-1)
		{
			z=0;
		for(i=20;i>j;i--)
		{
			a[i]=a[i-1];
		}
		a[j]=t;
	}
} 
 }
 for(i=0;i<21;i++)
 printf("%4d",a[i]); 
}
