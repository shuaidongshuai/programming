#include<stdio.h>
int main()
{
	long w[1000],n,i;
	w[1]=1,w[2]=1;
	printf(" ‰»Î£∫");
	scanf("%d",&n);
	for(i=3;i<=n;i++)
	w[i]=w[i-1]+w[i-2];
	 printf(" ‰≥ˆ£∫%ld",w[n]); 
 }
