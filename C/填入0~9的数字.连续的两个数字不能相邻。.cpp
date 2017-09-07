//填入0~9的数字。要求：连续的两个数字不能相邻。
//（左右、上下、对角都算相邻）
//一共有多少种可能的填数方案？
#include<stdio.h>
int a[5][6],b[10]={0,1,2,3,4,5,6,7,8,9},c[10],sum=0;
int init()
{
	for(int i=0;i<5;i++)
	for(int j=0;j<6;j++)
	a[i][j]=-2;
}
void change()
{
	int t=0;
	for(int i=1;i<4;i++)
	for(int j=1;j<5;j++)
	{
		if(i==1&&j==1||i==3&&j==4)
		continue;
		a[i][j]=b[t];
		t++;
	}
	/*for(int i=1;i<4;i++)
	for(int j=1;j<5;j++)
	{
		printf("%d ",a[i][j]);
	}
	printf("\n");*/
}
int solve()
{
	change();
	for(int i=1;i<4;i++)
	{
		for(int j=1;j<5;j++)
		{
			if(i==1&&j==1||i==3&&j==4)
			continue;
			if(a[i][j]==a[i-1][j]+1|| a[i][j]==a[i+1][j]+1 || a[i][j]==a[i][j+1]+1 || a[i][j]==a[i][j-1]+1 ||a[i][j]==a[i-1][j-1]+1 ||a[i][j]==a[i-1][j+1]+1 ||a[i][j]==a[i+1][j+1]+1 ||a[i][j]==a[i+1][j-1]+1)
			return 0;
			if(a[i][j]==a[i-1][j]-1|| a[i][j]==a[i+1][j]-1 || a[i][j]==a[i][j+1]-1 || a[i][j]==a[i][j-1]-1 ||a[i][j]==a[i-1][j-1]-1 ||a[i][j]==a[i-1][j+1]-1 ||a[i][j]==a[i+1][j+1]-1 ||a[i][j]==a[i+1][j-1]-1)
			return 0;
		}
	}
	return 1;
}
void dfs(int i)
{
	if(i>9)
	{
		int n=solve();
		if(n==1)
		sum++;
	}
	else
	{
		for(int j=0;j<10;j++)
		{
			if(c[j]==0)
			{
				b[i]=j;
				c[j]=1;
				dfs(i+1);
				c[j]=0;
			}
		}
	}
}
int main()
{
	init();
	dfs(0);
	printf("%d",sum);
 } 
