#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fd;
    char *mapped_mem;
    int flength = 1024;
	char buf[100] = "进程1:";

    fd = open("/home/dong/temp2", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    mapped_mem = (char*) mmap(0, flength, PROT_READ, MAP_SHARED, fd, 0);
	printf("地址：%x\n",(void *)mapped_mem);
	//memset(mapped_mem,0,1024);//注意对于刚创建的文件还没有任何东西，这时候去读它会出现段错误
    for(int i=0; i<10; i++)
    {
        printf("%s\n", mapped_mem);
        sleep(1);
    }

    munmap(mapped_mem, flength);
    close(fd);
    return 0;
}
