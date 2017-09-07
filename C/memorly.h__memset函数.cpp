#include<stdio.h>
#include<memory.h>
int main()
{
	char a[]="hello world";
	memset(a,'#',sizeof(a));
	printf("%s",a);
	memset(a,'*',sizeof(a));
	printf("%s",a);	
	memset(a,'1',sizeof(a));	
	printf("%s",a);	
 } 
