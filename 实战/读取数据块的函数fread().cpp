#include<stdio.h>
int main()
{
	char str[50];
	FILE *p;
	p=fopen("dong.txt","r");
	fread(str,2,2,p);
	printf("%s",str);
}
