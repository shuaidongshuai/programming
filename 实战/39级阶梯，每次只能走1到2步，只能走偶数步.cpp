#include<stdio.h>
int main()
{
	int i,j=19,k,l=0,t,n=1,u;
	for(i=1;i<=37;)
	{
		if((i+j)%2==0)
		{
			k=i+j;
			t=i<j?i:j;
			for(u=1;u<=t;u++)
			{
				n=n*k/u;
				k--;
			}
			if(u==t+1)
			l=l+n;
		} 
		n=1;
		j--;
		i=i+2;
	}
	printf("Êä³ö£º%d",l);
}
