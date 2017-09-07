#include<stdio.h>
int main()
{
	int a=1,b=1,n,sum=0;
	printf("输入n:\n");
	scanf("%d",&n);
	for(a=1;a<=n;a++)
	{
	b*=a;
	sum+=b;
	}
	printf("看看这是谁:%d\n",sum);
}
