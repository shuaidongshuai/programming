#include<stdio.h>
int a[3][4]={-1,0,1,2  ,3,4,5,6,  7,8,9,-1},b[10];
int main()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<=4;j++)
		printf("%-4d",a[i][j]);
		printf("\n");
	}

 } 
