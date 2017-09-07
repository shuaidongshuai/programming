#include<stdio.h>
int main()
{
	FILE *fp;
	fp=fopen("dong","r+");								//  文件必须存在	
	if(fp==NULL)
	{
		perror("open file textfile ");
		return 1;
	}
	
	fseek(fp,4,0);										// 0 的意思  就是  从开头开始   4 的意思就是  把指针向 右移动4个字节。（其实是五个字节，从零开始，，，数空隙就清楚了）
	char *p="hello world!!";
	fputs(p,fp);
	
	fseek(fp,2,1);										//  1  的意思就是  从当前开始   2 的意思和上面一样
	fputs("dong",fp);

	fseek(fp,-4,2);										//   2  的意思就是  从最后开始   -4 的意思就是 向左移动  4   个字节  注意 （是插空  相当于向左移动3个字节）
	fputs("bb",fp);
	
	fclose(fp);
	return 0;
}