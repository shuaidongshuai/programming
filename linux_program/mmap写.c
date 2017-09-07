#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int flength = 1024;
    int fd = open("/home/dong/temp2", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
											//S_IRUSR  Permits the file's owner to read it.
											//S_IWUSR  Permits the file's owner to write to it.
	printf("fd = %d\n",fd);
    char buf[100] = "进程2：";
	char *mapped_mem = (char*) mmap(0, flength, PROT_READ, MAP_SHARED, fd, 0);
	printf("地址：%x\n",(void *)mapped_mem);
    for(int i=0; i<5; i++)
    {   
        printf("%s\n", mapped_mem);
        sleep(1);
    }
	munmap(mapped_mem,flength);
	close(fd);
    return 0;
}
