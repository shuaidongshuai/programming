#include<stdio.h>
int main()
{
	float a[3][3];
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			scanf("%f",&a[i][j]);
		}
	}
		for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("%g\t",a[i][j]);
			if(j==2)
			printf("\n");	
		}
	}
}
