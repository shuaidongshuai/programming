// 创建进程思考结果
#include<stdio.h>
#include<unistd.h>
void main()
{
	pid_t pid;
	int a=0;
	pid=fork();								//  注意  创建的子进程  拷贝了父进程的数据  但绝不是共享
	a++;
	printf("a=%d\n",a);
}
