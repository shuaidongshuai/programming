#include <stdio.h>
int main(int argc,char **argv)
{
	if(argc != 2)
	  return 0;

	if(remove(argv[1]) != 0)//可以删除目录，unlink只能删除文件
	{
		printf("没有删除成功");
			return 0;
	}
	else
	{
		printf("删除成功");
	}
}

