#include<stdio.h>
int main()
{
	int a,b,c,t=0,j,n=0;
	for(a=4;a<100;a+=2)
		for(b=3;b<a-1;b+=2)
		{
			for(j=2;j<b;j++)
			{
				t=0;
				if(b%j==0)
				break;
				t=b;
			}
			if(t!=0)
			{
				c=a-b;
				if(b>=c)
				{
				for(j=2;j<c;j++)
				{
					t=0;
					if(c%j==0)
					break;
					t=c;
				}
				if(t!=0)
				{
					if(n%7==0) printf("\n");
					printf("%d=%d+%d   \t",a,b,c);
					n++;
				}
			}
		}
 }
 } 
