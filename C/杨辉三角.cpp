#include<stdio.h>
int main()
{
	int a[35][40]={0};
	int n,i,j;
	a[1][1]=1;
	scanf("%d",&n);
	if(n==1)
	printf("1\n");
	else
	{
	printf("1\n");
	for(i=2;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			a[i][j]=a[i-1][j-1]+a[i-1][j];
			if(a[i][j]==0)
			break;
			else
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}	
	 } 
	return 0;
}
