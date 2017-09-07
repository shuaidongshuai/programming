#include<stdio.h>
int main()
{
	FILE *fp;
	if((fp=fopen("dong","r"))==NULL)
	{
		printf("不能打开文件");
		return 1;
	}
	printf("current pointer	position = %ld\n",ftell(fp));
	char ch;
	ch=fgetc(fp);
	while(ch!=EOF)			// 读错  或者  读 到  文件末尾  会返回  EOF
	{
		putchar(ch);
		ch=fgetc(fp);
	}
	printf("\n");
	printf("current pointer position = %ld\n",ftell(fp));
	rewind(fp);
	printf("After using the rewind \ncurrent pointer position = %ld\n",ftell(fp));
	
	fclose(fp);
}