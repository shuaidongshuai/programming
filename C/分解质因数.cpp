#include<stdio.h>
int main()
{
	int n,i=2;
	printf("请输入一个数:");
	scanf("%d",&n);
	printf("看哥是多么神勇：%d=",n);
	for(;i<=n;i++)
	{
	while(n!=i)
	{
		if(n%i==0)
		{
		printf("%d*",i);
		n/=i;
		}
		else
		break; 
	}
	} 
	printf("%d",n);
}
