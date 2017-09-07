#include<stdio.h>
int main()
{
	FILE *p;
	char ch;
	p=fopen("G:\\b.txt","a");
	if(p==NULL)
	{
		printf("can't open file");
	 } 
	 	 while(ch!='\n')
	 {
	 	ch=getchar();
	 	fputc(ch,p);
	 }
	 fclose(p);
 } 
