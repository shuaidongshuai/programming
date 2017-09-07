#include<stdio.h>
int main()
{
	FILE *p;
	char f[50],ch;
	gets(f);
	p=fopen(f,"r");
	ch=fgetc(p);
	while(ch!='2')
	{
		putchar(ch);
		ch=fgetc(p);
	}
	fclose(p);
 } 
