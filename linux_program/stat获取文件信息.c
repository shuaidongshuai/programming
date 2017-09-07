#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
void main()
{
	struct stat buf;
	stat("./1.txt",&buf);								// 获取文件信息   放在 buf  里面
	printf("1 file size = %d\n",(int)buf.st_size);		//  调用结构体   查看   文件里面的  各种信息
	printf("a file owner UID = %d\n",buf.st_uid);
	printf("a file owner GID = %d\n",buf.st_gid);
}