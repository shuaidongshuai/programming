#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void pidError(pid_t pid)
{
	if(pid<0)
	{
		perror("fork error");
		exit(0);
	}
}

int main()
{
	pid_t pid = fork();//第一步		创建子进程
	pidError(pid);
	
	 if(pid>0)//第二步		结束父进程
        exit(0);
	
	pid = setsid(); //第三步		
	pidError(pid);
	
	//int chdir(const char *path);  On success, zero is returned.  On error, -1 is returned,
	chdir("/"); //第四步
	
	umask(0); //第五步
	
	 for(int i=0;i<3;i++) //第六步
        close(i);
		
		
	//下面是测试守护进程（每隔10ms在/tmp/dameon.log中写入一句话）
	char buf[] = "my first dameon守护进程";
	while(1)
	{
		int fd;
		if(fd = open("/tmp/dameon.log",O_CREAT|O_WRONLY|O_APPEND,0600))//O_WRONLY只写模式	O_APPEND的含义是在每次写之前，都讲标志位移动到文件的末端。
		{
			printf("open error");
			exit(0);
		}
		write(fd,buf,strlen(buf));
		close(fd);
		usleep(100*1000); //100毫秒
	}
}

// （1）setsid函数作用：
// setsid函数用于创建一个新的会话，并担任该会话组的组长。调用setsid有下面的3个作用：
// 让进程摆脱原会话的控制
// 让进程摆脱原进程组的控制
// 让进程摆脱原控制终端的控制

// 那么，在创建守护进程时为什么要调用setsid函数呢？
// 由于创建守护进程的第一步调用了fork函数来创建子进程，再将父进程退出。
// 由于在调用了fork函数时，子进程全盘拷贝了父进程的会话期、进程组、控制终端等，
// 虽然父进程退出了，但会话期、进程组、控制终端等并没有改变，
// 因此，这还不是真正意义上的独立开来，而setsid函数能够使进程完全独立出来，从而摆脱其他进程的控制。

// （2）改变当前目录为根目录
// 这一步也是必要的步骤。使用fork创建的子进程继承了父进程的当前工作目录。
// 由于在进程运行中，当前目录所在的文件系统（如“/mnt/usb”）是不能卸载的，
// 这对以后的使用会造成诸多的麻烦（比如系统由于某种原因要进入单用户模式）。
// 因此，通常的做法是让"/"作为守护进程的当前工作目录，这样就可以避免上述的问题，
// 当然，如有特殊需要，也可以把当前工作目录换成其他的路径，如/tmp。改变工作目录的常见函数是chdir。

// （3）重设文件权限掩码
// 文件权限掩码是指屏蔽掉文件权限中的对应位。
// 比如，有个文件权限掩码是050，它就屏蔽了文件组拥有者的可读与可执行权限。
// 由于使用fork函数新建的子进程继承了父进程的文件权限掩码，这就给该子进程使用文件带来了诸多的麻烦。
// 因此，把文件权限掩码设置为0，可以大大增强该守护进程的灵活性。设置文件权限掩码的函数是umask。在这里，通常的使用方法为umask(0)。

// （4）关闭文件描述符
// 同文件权限码一样，用fork函数新建的子进程会从父进程那里继承一些已经打开了的文件。
// 这些被打开的文件可能永远不会被守护进程读写，但它们一样消耗系统资源，而且可能导致所在的文件系统无法卸下。
// 在上面的第二步之后，守护进程已经与所属的控制终端失去了联系。
// 因此从终端输入的字符不可能达到守护进程，守护进程中用常规方法（如printf）输出的字符也不可能在终端上显示出来。
// 所以，文件描述符为  0、1和2    的3个文件（常说的输入、输出和报错）已经失去了存在的价值，也应被关闭。



