#include<stdio.h>
int main()
{
	int i,j,k,sum=0;
	for(i=1;i<5;i++)
	{
		for(j=1;j<5;j++)
		{
			for(k=1;k<5;k++)
			{
			if(i!=k&&k!=j&&i!=j)
			{ 
			printf("%d%d%d\n",i,j,k);
			sum=sum+1;
		}
		}
		}
	}
	printf("一共%d个数",sum);
}
