#include<stdio.h>
int main()
{
	int t,y,n,a,i=0,c=0;
	scanf("%d%d",&a,&n);
	t=a;
	printf("a=%d,n=%d\n",a,n);
	while(i<n)
	{
		y=y+a;
		c+=y;
		a=a*10;
		i++;
	}
	printf("%d+%d+```+%d=%d",t,11*t,y,c);
}
