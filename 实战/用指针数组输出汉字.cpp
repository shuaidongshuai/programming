#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char (*p)[2];
	p=(char (*)[2])malloc(4*sizeof(char ));
	strcpy(p[0],"¶«");
	printf("%s\n",p[0]);
	return 0;
}
