#include<iostream>
int main()
{
	int i,n=0;
	for(i=0;i<99;i++)
	{
		if(i%2!=0) continue;
		printf("%d+",i+1);
		n+=i+1;
		if(i%5==0&&i!=0) printf("\n"); 
	}
	printf("100=%d",n);
 } 
