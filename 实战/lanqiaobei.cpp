#include<stdio.h>
int main()
{
	int a,b,c,d,e,f;
	for(a=1;a<10;a++)
	for(b=0;b<10;b++)
	for(c=0;c<10;c++)
	for(d=0;d<10;d++)
	for(e=1;e<10;e++)
	for(f=1;f<10;f++)
	{
		if(a!=b&&a!=c&&a!=d&&a!=e&&b!=c&&b!=d&&b!=e&&c!=d&&c!=e&&d!=e)
		if((a*10000+b*1000+c*100+d*10+e)*f==(e*10000+d*1000+c*100+b*10+a))
			printf("%d  %d  %d  %d  %d\n",a,b,c,d,e);
	}
}
