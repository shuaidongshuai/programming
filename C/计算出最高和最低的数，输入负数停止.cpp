#include <stdio.h>
int main()
{
	float x,max,min;
	scanf("%f",&x);
	max=x;
	min=x;
	while(x>=0.0)
	{
		if(x>=max)
		max=x;
		if(min>=x)
		min=x;
		scanf("%f",&x);
	}
	printf("\nmax=%f\nmin=%f\n",max,min);
}
