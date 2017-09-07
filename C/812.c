#include<stdio.h>
int main(int a,char *argv[])
{
	int i;
	printf("a=%d\n",a);
	printf("argv=");
	for(i=1;i<a;i++)
	printf("%s",argv[i]);
}
