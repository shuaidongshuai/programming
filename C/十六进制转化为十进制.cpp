#include<stdio.h>
#include<string.h>
int main()
{
	char str1[10];
	scanf("%s",str1); 
	int i,length;
	long long sum=0,n=1;
	length=strlen(str1);
	for(i=length-1;i>=0;i--)
	{
		if(str1[i]<58)
		sum+=(str1[i]-'0')*n;
		else if(str1[i]<72)
		sum+=(str1[i]-'A'+10)*n;
		n*=16;
	}
	printf("%lld",sum);
	return 0;
 } 
