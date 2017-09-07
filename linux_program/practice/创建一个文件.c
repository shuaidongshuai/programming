//实验要求 创建一个可读可写 的文件
//create函数也能打开一个文件，如果文件不存在，则创建它。和open一样，creat也在调用成功后返回一个文件描述符，如果失败，则设置errno变量并返回-1.
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
int  main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("a.out == cp");
		return 1;
	}
	else{
		for(int i=1;i<argc;i++)
		{
			if(creat(argv[i],0755)<0)
			{
				printf("creat file is %s fail\n",argv[i]);
				return 1;
			}
			else
			{
				printf("creat file is%s success\n",argv[i]);
			}
		}
	}
	return 0;
}
//  自己做的时候  就用了 一个 creat 函数  这个代码  还是看的答案  很完善  特别是哪个for  循环  很受教