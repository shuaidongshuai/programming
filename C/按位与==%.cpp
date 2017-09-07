#include<stdio.h>
int main()
{
	int i,n;
	for(i=0;i<=10;i++)
	printf("%d\t%%2\t=%d\n",i,i&1);// 按位与  比 %2  快得多 
 } 
