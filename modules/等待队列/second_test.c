#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    unsigned char key_val;
    int fd ;
	fd = open("/dev/irq_dev",O_RDWR);
	if(fd<0)
	{
		printf("can't open");
		return 0;
	}
	while(1)
	{
		read(fd,&key_val,1);
		printf("key_val = 0x%x\n",key_val);
	}

	return 0;
}
