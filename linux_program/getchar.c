#include<stdio.h>
int main()
{
	FILE *fp;
	char ch;
	if((fp=fopen("dong","a"))==NULL)
	{
		perror("fopen error");
		return 1;
	}
	printf("input a string:\n");

	
/*	ch=getchar();							//  从你输入在屏幕上的字符  以追加的方式  写入到  dong 这个文件  中
	while(ch!='\n')							//  以 回车键  结束  输入  （但是我想在dong 这个文件中加一个 回车就不会加了     因为按了回车就不能 写入到文件中了）
	{
		fputc(ch,fp);
		ch=getchar();
	}	*/
	//  由于我想  把  回车键  加入到  文件中  所以我想出了  下面的方法进行 输入
	
	
	ch=getchar();
	fputc(ch,fp);
	while(ch!='\n')
	{
		ch=getchar();
		fputc(ch,fp);
	}
	printf("\n");
	fclose(fp);
	return 1;
}