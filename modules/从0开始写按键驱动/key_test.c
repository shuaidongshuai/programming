#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd;
	unsigned char key_vals[6];
	int cnt=0;
	
	fd = open("/dev/key", O_RDWR);
	
	while(1)
	{
		read(fd,key_vals,sizeof(key_vals));
		if (!key_vals[0] || !key_vals[1] || !key_vals[2] || !key_vals[3] || !key_vals[4] || !key_vals[5])
		{
			printf("%-4d key pressed: %d %d %d %d %d %d \n", cnt++, key_vals[0], key_vals[1], key_vals[2], key_vals[3], key_vals[4] , key_vals[5]  );
		}
	}
	
	return 0;
}