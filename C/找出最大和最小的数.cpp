#include<stdio.h>
int main()
{
	int c,b,n,a[10001];
	scanf("%d",&n);
	int i;
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	c=b=a[0];
	for(i=1;i<n;i++)
	{
		if(c<a[i])
		c=a[i];
		else if(b>a[i])
		b=a[i];
	}
	printf("%d %d",c,b);
	return 0;
 } 
