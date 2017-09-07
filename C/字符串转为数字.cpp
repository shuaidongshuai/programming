#include<stdio.h>
int main()
{
	char a[]="1234";
	int n=0,t=1000; 
	for(int i=0;i<sizeof(a)-1;i++)
	{
		n+=(a[i]-'0')*t;
		t/=10;
	}
	printf("%d",n);
	return 0;
 } 
