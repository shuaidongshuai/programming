#include<stdio.h>
void up(int a[][4],int i)
{
	int j,k,t;
	for(j=0;j<3;j++)
	for(k=0;k<3-j;k++)
	{
		if(a[i][k]>a[i][k+1])
		{
			t=a[i][k];
			a[i][k]=a[i][k+1];
			a[i][k+1]=t;
		 } 
	}
 } 
 void down(int a[][4],int i)
 {
 	int j,k,t;
	for(j=0;j<3;j++)
	for(k=0;k<3-j;k++)
	{
		if(a[i][k]<a[i][k+1])
		{
			t=a[i][k];
			a[i][k]=a[i][k+1];
			a[i][k+1]=t;
		 } 
	}
 }
int main()
{
	printf("原始数据如下：\n");
	int j,i,a[4][4]={{2,3,4,1},{8,6,5,7},{11,12,10,9},{15,14,16,13}};
		for(i=0;i<4;i++)
	{
	for(j=0;j<4;j++)
	printf("%5d",a[i][j]);
	printf("\n");
} 
printf("排序后：\n");
	for(i=1;i<=4;i++)
	{
		if(i%2==0)
		up(a,i-1);
		else
		down(a,i-1);
	}
	for(i=0;i<4;i++)
	{
	for(j=0;j<4;j++)
	printf("%5d",a[i][j]);
	printf("\n");
} 
}
