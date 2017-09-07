#include <stdio.h>
int main()
{
	int c,r,m,n,a,b;
	scanf("%d,%d",&m,&n);
	a=m,b=n;
	if(m<n)
	{
		c=m;m=n;n=c;
	}
	r=m%n;
	while(r!=0)
	{
		m=n;n=r;r=m%n;
	 } 
	 printf("%d,%d",n,a*b/n);
}
