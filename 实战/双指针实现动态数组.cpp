#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i,j,row,line,**p;//这我们定义一个双指针   行列  都由用户自己输入
	printf("输入行：");
	scanf("%d",&row);
	printf("输入列：");
	scanf("%d",&line);
	p=(int **)malloc(row*sizeof(int *));
	if(NULL==p)
	{
		return 0;
	}
	for(i=0;i<line;i++)
	*(p+i)=(int *)malloc(line*sizeof(int));
	if(NULL==p)
	{
		return 0;
	}
	for(i=0;i<row;i++)
	{
		for(j=0;j<line;j++)
		{
			p[i][j]=i+j;
			printf("%5d",p[i][j]);
		}
		printf("\n");
	}
}
