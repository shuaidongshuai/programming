#include<stdio.h>
int M,N,w[100],p[100];
int max(int a,int b)
{
	if(a<b)
	a=b;
	return a;
}
int solve(int i,int m)
{
	int result=0;
	if(i>=m)
	return result;
	if(w[i]>m)
	solve(i+1,m);									// 不存在选不选 的问题   是不能选 
	else
	return result=max(solve(i+1,m),solve(i+1,m-w[i])+p[i]);		//这就是 选不选的 问题了 
}
int main()
{
	scanf("%d%d",&N,&M);
	int i,j;
	for(i=0;i<N;i++)
	{
		scanf("%d%d",&w[i],&p[i]);
	}
	int result=solve(0,M);
	printf("%d",result);
 } 
