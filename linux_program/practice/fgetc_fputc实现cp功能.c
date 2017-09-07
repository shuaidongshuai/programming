//  第二种是库函数  时间cp  功能
#include<stdio.h>
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("a.out file file2\n");
		return 1;
	}
	FILE *fp1,*fp2;
	fp1=fopen(argv[1],"r");
	fp2=fopen(argv[2],"a");
	char ch;
	while(1)
	{
		char ch=fgetc(fp1);
		if(ch!=EOF)
		{
			fputc(ch,fp2);
		}
		else{
			break;
		}
	}
	return 1;
}
//  这种复制  思想很简单  就一个循环   优点就是  不用去在意他的字节数  是多少