#include<stdio.h>
int a[101][2];
int max(int a,int b)
{
	if(a<=b)
	a=b;
	return a;
}
int choose(int left,int right,int i)
{
	if(i<0)
	{
		return 0;
	}
	else
	{
		int t;
		left+=a[i][0];
		right+=a[i][1];
		printf("i=%d\t%d\t%d\t%d\n",i,a[i][0],a[i][1],left+right);
		t=max(choose(left,right,i-1)+a[i][0]+a[i][1],choose(left-a[i][0],right-a[i][1],i-1));
		if(left>0&&right>0&&a[i][0]+a[i][1]>0);
		return t;
	}
}
int main()
{
	int i,n;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&a[i][0],&a[i][1]);
	}
	printf("%d",choose(0,0,n-1));
	return 0;
 } 
