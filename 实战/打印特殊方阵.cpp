#include<stdio.h>
int main()
{
	int n=0,a[20][20],i,j;
	for(i=1;i<11;i++)
	for(j=i;j<21-i;j++)
	{
		a[i][j]=i;
		a[20-i][j]=i;
		a[j][i]=i;
		a[j][20-i]=i;
	}
	for(i=1;i<20;i++)
	{
	for(j=1;j<20;j++)
	printf("%3d",a[i][j]);
	printf("\n");
 } 
}
