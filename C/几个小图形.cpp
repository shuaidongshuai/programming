#include<stdio.h>
int main()
{
	int i,j;
	for(i=0;i<=10;i++)
	{
		for(j=0;j<=i;j++)
		printf("*");
		for(j=0;j<=10-i;j++)
		printf(" ");
		printf("\t");
		for(j=0;j<=10-i;j++)
		printf(" ");
		for(j=0;j<=i;j++)
		printf("*");
		printf("\n");
	}
	printf("\n");
	for(i=10;i>=0;i--)
	{
		for(j=0;j<=i;j++)
		printf("*");
		for(j=0;j<=10-i;j++)
		printf(" ");
		printf("\t");
		for(j=0;j<=10-i;j++)
		printf(" ");
		for(j=0;j<=i;j++)
		printf("*");
		printf("\n");
	}
	int a=14,b=10;
	for(i=1;i<=10;i++)
	{
		for(j=1;j<=a;j++)
		printf(" ");
		for(j=1;j<=i*2-1;j++)
		printf("*");
		for(j=1;j<=a;j++)
		printf(" ");
		
		for(j=--b;j>=0;j--)
		printf(" ");
		for(j=0;j<10;j++)
		printf("*");
		printf("\n");
		a--;
	} 
	a=15; 
		for(i=1;i<=10;i++)
	{
		for(j=1;j<=a;j++)
		printf(" ");
		for(j=1;j<=i*2-1;j++)
		printf("*");
		a--;
		printf("\n");
	}
	a=0;
	for(i=1;i<=10;i++)
	{
		for(j=1;j<=i+5;j++)
		printf(" ");
		for(j=1;j<20-a;j++)
		printf("*");
		printf("\n");
		a+=2;
	}
 } 
