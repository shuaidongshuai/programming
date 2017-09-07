//从原点出发，一步只能向右走、向上走或向左走。恰好走N步且不经过已走的点共有多少种走法 
// 比 递推1 容易理解 
#include<stdio.h>
int main()
{
	int i,n,f[2],t;
	while(1)
	{
		f[0]=3,f[1]=7;
		scanf("%d",&n);
		if(n==1)
			printf("3\n");
		else if(2==n)
			printf("7\n");
		else
		{
			for(i=3;i<=n;i++)//从这开始就是  递推 f(n)=2*f(n-1)+f(n-2)
			{
				t=	2*f[1] + f[0];
				f[0] = f[1];
				f[1] = t; 
			}
			printf("%d\n",f[1]);
		}
	}
	return 0;
}
