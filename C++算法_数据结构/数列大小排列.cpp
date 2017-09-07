#include"sort.h"
#include<stdio.h>
int main()
{
	int k,a[10]={4,9,8,7,6,1,0,2,3,5};
	sort(a,10);
	for(k=0;k<10;k++)
	{
	printf("%d ",a[k]);
}
return 0;
}
