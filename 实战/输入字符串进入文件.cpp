#include<stdio.h>
int main()
{
	FILE *p;
	p=fopen("dong1.txt","a");
	char st[88];
	gets(st);
	fputs(st,p);
}
