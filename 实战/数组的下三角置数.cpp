#include<stdio.h>
int main()
{
	printf("请输入一个4*4的数组\n");
	int a[4][4],j,i;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			scanf("%5d",&a[i][j]);
	printf("你输入的数组是:\n");
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			printf("%5d",a[i][j]);
		printf("\n");
	}
	printf("你输入数组的下三角置数是：\n");
	for(i=0;i<4;i++)
	{
		for(j=0;j<=i;j++)
			printf("%5d",a[i][j]);
		printf("\n");
	}
}
