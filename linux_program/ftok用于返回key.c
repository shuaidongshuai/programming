#include<sys/types.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<stdio.h>
int main(void)
{
	key_t key;
	for(int i=0;i<20;i++)
	{
		key=ftok("/home/dong/dd/1",i);
		printf("key=%x\n",key);
		sleep(1);
	}
	return 0;
}