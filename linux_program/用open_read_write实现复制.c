#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>		//以上三个函数调用 open 函数

#include<unistd.h>		//调用read write函数

#include<stdio.h>
#define SIZE 4
int main(int argc,char *argv[])
{
	int from_fd,to_fd;
	char buf[4];
	if(argc==1)
	{
		printf("a.out == cp\n");
		return 1;
	}
	from_fd=open(argv[1],6);
	to_fd=open(argv[2],O_CREAT|O_RDWR,0766);				//刚开始出错  把这一步 放在了  下面  1 处   导致  每次打开指针都指向开头  不能实现连续拷贝
	
	int rdsize;
	while((rdsize=read(from_fd,buf,SIZE)) != 0)
	{	
															//  1  
		write(to_fd,buf,rdsize);
		printf("%s\n",buf);
	}
	return 0;
}
