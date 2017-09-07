#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int fd;
    char filename[20];
	int arg = atoi(argv[1]);
    if (argc != 3)
    {
        printf("./dong_led 1 off\n");
        return 0;
    }

    sprintf(filename,"/dev/led%s",argv[1]);
    fd = open(filename, O_RDWR);
    if (fd < 0)
    {
        printf("error, can't open %s\n", filename);
        return 0;
    }

    if (!strcmp("on", argv[2]))
    {
        // 亮灯
        ioctl(fd, 0,arg);
    }
    if (!strcmp("off", argv[2]))
    {
        // 灭灯
        ioctl(fd, 1,arg);
    }

    return 0;
}

