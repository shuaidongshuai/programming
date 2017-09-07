#include<stdio.h>
int main()
{
	int i;
	char str[2][10];
	char str2[2][10];
	FILE *fp;
	fp=fopen("D:\\dong.dat","a+");
	for(i=0;i<3;i++)
	{
		gets(str[i]);
		fputs(str[i],fp);
		fputs("\n",fp);
	}
//	fclose(fp);
	//必须重新打开   或者用fseek 
//	fp=fopen("D:\\dong.dat","a+");

	fseek(fp,1L,0);	// 第二个参数 表示 当前位置 ，以起始点为准   如  1L  就是从第一个字符开始，正常是从0 开始的。。。第二个参数  0  代表文件开始 
	for(i=0;i<3;i++)
	{
		fgets(str2[i],sizeof(str[i]),fp);	
		printf("%s",str2[i]);
	}

 } 
