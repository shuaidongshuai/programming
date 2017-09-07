#include<stdio.h>
int main()
{
	FILE *fp;
	int num=0;
	fp=fopen("a.txt","r");
	if(fp==NULL) 
	{
		printf("file");
	}
	while(!feof(fp))
	{
		fgetc(fp);
		num++;
	}
	printf("num=%d\n",num);
	fclose(fp);
 } 
