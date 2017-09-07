#include<stdio.h>
int a,sum=0;
int aa(int q)
{
	if(q==1)
	{
		return sum;
	}
	else
	{
		if(q>1)
		{
			sum++;
			a-=127;
		}
		else
		{
			sum++;
			a+=97;
		}
	}
 } 
 int main()
 {
 	int t = aa(0);
 	printf("%d",t);
 	return 0;
 }
