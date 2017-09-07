#include<stdio.h>
//从大到小排序 
int main()
{
	int a[5],i,j;
	for(i=0;i<5;i++)
	scanf("%d",&a[i]);
	for(i=0;i<5;i++)
	for(j=0;j<5-i-1;j++)		//这里 j<5-i-1  是因为冒泡没次都把最小放到最后   也可以j<5 或  j<4  只是这样没有必要 多循环了几次 
	if(a[j]<a[j+1])
	{
		int t=a[j];
		a[j]=a[j+1];
		a[j+1]=t;
	}
	for(j=0;j<5;j++)
	printf("%d",a[j]);	
}
