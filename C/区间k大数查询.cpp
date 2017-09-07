/*问题描述
给定一个序列，每次询问序列中第l个数到第r个数中第K大的数是哪个。

输入格式
第一行包含一个数n，表示序列长度。

第二行包含n个正整数，表示给定的序列。

第三个包含一个正整数m，表示询问个数。

接下来m行，每行三个数l,r,K，表示询问序列从左往右第l个数到第r个数中，从大往小第K大的数是哪个。序列元素从1开始标号。

输出格式
总共输出m行，每行一个数，表示询问的答案。
样例输入
5
1 2 3 4 5
2
1 5 2
2 3 2
样例输出
4
2
数据规模与约定
对于30%的数据，n,m<=100；

对于100%的数据，n,m<=1000；

保证k<=(r-l+1)，序列中的数<=106。*/
#include<stdio.h>
#include<string.h>
void quick(int a[],int left,int right)
{
	int l = left;
	int r = right;
	int t = a[l];
	
	if(l<r)
	{
		while(l<r)
		{
			while(l<r&&a[r]<=t)
			r--;
			a[l] = a[r];
			while(l<r&&a[l]>=t)
			l++;
			a[r] = a[l];
			if(l>=r)
			break;
		}
		a[l] = t;
		quick(a,left,r-1);
		quick(a,l+1,right);		
	}
}


int main()
{
	int i,j,a[1000],b[3],c[1000],d[1000],n,No;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	
	scanf("%d",&No);
	for(i=0;i<No;i++)
	{
		for(j=0;j<3;j++)
		scanf("%d",&b[j]);
		
		memcpy(c,a,sizeof(a));		
		quick(c,b[0]-1,b[1]-1);
		d[i] = c[b[0]-1+b[2]-1];
	}
	
	for(i=0;i<No;i++)
	printf("%d\n",d[i]);
	return 0;
 } 
