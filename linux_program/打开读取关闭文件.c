#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
void main()
{
	DIR	*dir;						//
	struct dirent *ptr;
	int i;
	dir=opendir("/home/dong/dd");	//返回 DIR* 目录形态流
	while((ptr=readdir(dir))!=NULL)	//用了opendir 的返回值       	返回了  struct dirent *  这个返回值
	{
		printf("%s\n",ptr->d_name);
	}
	closedir(dir);
}