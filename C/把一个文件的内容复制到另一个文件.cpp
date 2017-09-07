#include<stdio.h>
int main()
{
	FILE *f1,*f2;
	char c;
	f1=fopen("dong.txt","r");
	if(f1==NULL)  printf("can't open file");
	f2=fopen("dong2.txt","w"); 
	while(!feof(f1))
	{
		c=fgetc(f1);
		fputc(c,f2);
	}
 } 
