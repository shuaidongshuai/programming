#include <stdio.h>
 #include <stdlib.h>

int test()
{
	extern char **environ;
	for(int i = 0;environ[i]!=NULL;i++)
		printf("%s\n",environ[i]);
	return 0;
}

int main()
{
	printf("PATH=%s\n", getenv("PATH"));//获取环境变量
	setenv("PATH", "hello", 1);//设置环境变量
	printf("PATH=%s\n", getenv("PATH"));
	return 0;
}