#include<stdio.h>
#include<math.h>
int main()
{
	int a,b,c,d,e;
	for(a=1;;a++)
	{
	b=a+100;
	c=sqrt(b);
	if(c*c==b)
	{
		d=b+168;
		e=sqrt(d);
		if(e*e==d)
		{
		printf("%d",a);
		break;
	}
	}
}
 } 
