#include<string.h>
#include<stdio.h>
int main()
{
	int i,j,k;
	char a[100];
	gets(a);
	for(i=0,j=strlen(a)-1;i<j;i++,j--)
	{
		k=a[i];
		a[i]=a[j];
		a[j]=k;
	}
	printf("Êä³ö£º");
	puts(a); 
 } 
