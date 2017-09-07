#include<stdio.h>
#include<stdlib.h>
int main()
{
	int *a= 0,n,i,sum=0;
	scanf("%d",&n);
	a=(int *)malloc(sizeof(int )*n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	printf("%d %d",sum,sum/n);
	return 0;
 } 
