#include<stdio.h>
int N,M,w[201],v[201];
int max(int a,int b)
{
	if(a<b)
	a=b;
	return a;
}
int select(int i,int m)
{
	if(i>=N||w[i]==0)
	return 0;
	else
	{
		if(m>=w[i])
		return max(select(i+1,m),select(i+1,m-w[i])+v[i]);
		else
		select(i+1,m);
	}
}
int main()
{
	int i;
	scanf("%d%d",&N,&M);
	for(i=0;i<N;i++)
	{
		scanf("%d%d",&w[i],&v[i]);
	}
	printf("%d",select(0,M));
	return 0;
 } 
