#include<stdio.h>
int main()
{
	int i,t,m,n;
	printf("输入两个数：");
	scanf("%d%d",&n,&m);
	if(n>m)
	{
		t=m;
		m=n;
		n=t;
	}
	for(i=n;i>0;i--)
	{
		if(m%i==0&&n%i==0)
		{
			printf("最大公约数：%d\n最大公倍数：%d",i,m*n/i);
			break;
		}
	}
}
