#include<stdio.h>
int a[1000001];
int main()
{
	int i,n;
	a[1]=a[2]=1;
	scanf("%d",&n);
	for(i=3;i<=n;i++)
	{
		a[i]=(a[i-2]+a[i-1])%10007;	
	}
	printf("%d",a[n]);
	return 0;
 } 
