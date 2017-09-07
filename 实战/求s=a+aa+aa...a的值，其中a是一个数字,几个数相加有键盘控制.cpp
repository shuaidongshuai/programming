#include<stdio.h>
#include<math.h>
int main()
{
	int n,sum=0,a;
	printf("a=");
	scanf("%d",&a);
	printf("n=");
	scanf("%d",&n);
	while(n!=0)
	{
		sum+=a*(pow(10,n)-1)/9;
		n--;
	}
	printf("%d",sum);
	return 0;
 } 
