#include"maopaos.h" 
#include<stdio.h>
#include<time.h> 
int main()
{
	int n,k,a[10000];
	srand(time(NULL));
	printf("你想要排列几个数:");
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		a[k]=rand()*100/32767;
	}
	small(a,n);
	for(k=0;k<n;k++)
	{
	if(k%10==0&&(k!=0))
	printf("\n");
	printf("%d\t",a[k]);
}
}
