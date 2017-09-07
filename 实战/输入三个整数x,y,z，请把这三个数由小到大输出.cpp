#include<stdio.h>
int main()
{
	int a[3],t,i,j;
	scanf("%d,%d,%d",&a[0],&a[1],&a[2]);
	for(j=0;j<3;j++)
	{
		for(i=0;i<2-j;i++)
		{
			if(a[i]>a[i+1])
			{
			t=a[i];
			a[i]=a[i+1];
			a[i+1]=t;
		}
		}
	}
	for(i=0;i<3;i++)
	{
	printf("%d, ",a[i]);
	} 
 } 
