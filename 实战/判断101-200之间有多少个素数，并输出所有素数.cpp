#include<stdio.h>
#include<math.h>
int main()
{
	int i,j,leap=0;
	for(i=101;i<200;i++)
	{
		for(j=2;j<sqrt(i);j++)
		{
			if(i%j==0)
			i++;
			break;
		}
		leap++; 
		printf("%d\t",i);
	 } 
	 		printf("\n×ÜÊý%d",leap);
 } 
