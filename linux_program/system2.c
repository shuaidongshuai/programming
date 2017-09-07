#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
//×Ô¼ºÐ´systemº¯Êý

int mySystem(const char* cmd)
{
	// if(cmd == NULL)
	// {
		// return 1;
	// }
	pid_t pid;
	int status;
	if((pid = fork()) < 0)
	{
		status = -1;
	}
	else if(0 == pid)
	{
		execl("/bin/sh","sh","-c",cmd,NULL);//int execl(const char *path, const char *arg, ...
		exit(127);
	}
	else
	{
		while(waitpid(pid,&status,0) < 0)
		{
			//EINTR           Interrupted function call (POSIX.1); see signal(7).
			if(errno == EINTR)
				continue;
			status = -1;
			break;
		}
	}
	return status;
}

int main(int argc,char** argv)
{
	printf("%d\n",argc);
	// if(argc > 2)
		// return 0;
	printf("%d\n",mySystem(argv[1]));
}