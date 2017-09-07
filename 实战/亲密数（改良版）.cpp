#include<stdio.h>
int main()
{
	int n,a,i,b;
	for(a=1;a<10000;a++)
	{
		for(b=0,i=1;i<=a/2;i++)
			if(a%i==0)
				b+=i;
			if(a<b)
			{
			for(i=1,n=0;i<=b/2;i++)
				if(b%i==0)
					n+=i;
				if(a==n)
					printf("%d  %d\n",a,b);
			}
	}
}
