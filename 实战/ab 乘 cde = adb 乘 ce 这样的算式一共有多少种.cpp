#include<stdio.h>
int main()
{
	int a,b,c,d,e,n=0;
	for(a=1;a<10;a++)
	{
		for(b=1;b<10;b++)
		{
			for(c=1;c<10;c++)
			{
				for(d=1;d<10;d++)
			{
					for(e=1;e<10;e++)
					{
						if((a*10+b)*(c*100+d*10+e)==(a*100+d*10+b)*(c*10+e)&&a!=b&&a!=c&&a!=d&&a!=e&&b!=c&&b!=d&&b!=e&&c!=d&&c!=e&&d!=e)
						{
						n++;
						printf("%3d,%3d,%3d,%3d,%3d\n",a,b,c,d,e);
					}
					}
				}
			}
		}
	}
	printf("%d",n);
 } 
