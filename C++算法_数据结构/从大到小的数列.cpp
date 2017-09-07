#include<stdio.h>
#include"maopaos.h"
#include<time.h>
#include<stdlib.h>
int main()
{
	int n,k,a[10000];
	printf("你想要排列几个数:");
	scanf("%d",&n);
	srand(time(NULL));
	for(k=0;k<n;k++)
	{
		a[k]=rand()*100/32767;
	}
	small(a,n);
	for(k=n-1;k>=0;k--)
	{
	printf("%d\t",a[k]);
		if(k%10==0)
	printf("\n");
}
}
