#include <unistd.h>
#include <stdio.h>
int main(int argc,char **argv)
{
	if(argc != 2)
	  return 0;

	if(unlink(argv[1]) != 0)//只能删除文件，删除目录要用remove
	{
		printf("没有删除成功");
		return 0;
	}
	else
	{
		printf("删除成功");
	}
}

