#include<stdio.h>
#include<ctype.h>
int main()
{
	char i;
	char p;
	i=getchar();
	isalpha(i)?(p='y'):(p='n');
	printf("%c\t",p);
 } 
