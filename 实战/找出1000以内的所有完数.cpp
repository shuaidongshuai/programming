#include<stdio.h>
int main()
{
	int i,j,sum=0;
	printf("1000以内的完数有：\n");
	for(j=4;j<1000;j++)
	{
	for(i=1;i<j;i++)
	{
		if(j%i==0)
		{
			sum+=i;
		}
	 } 
	 if(sum==j)
	 {
	 	printf("%d\t",j);
	 }
	 sum=0;
}
}
