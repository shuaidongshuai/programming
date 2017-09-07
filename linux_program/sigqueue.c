#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

typedef struct Teacher
{
	char name[12];
	int age ;
}Teacher;

//演示两个进程间通过 sigqueue 发送数据
//struct sigaction act;
//	act.sa_sigaction = myHandle_forsigaction; 接受数据

 // If the receiving process has installed a handler for this  signal  using
// the  SA_SIGINFO  flag  to sigaction(2), then it can obtain this data via
//意思就是，接收的进程需要一个handler函数来接收数据，而且进程需要在sigaction的sa_flags位设置一个SA_SIGINFO才能获得数据

// the si_value field of the siginfo_t structure passed as the second argu‐
// ment  to  the handler.  Furthermore, the si_code field of that structure
// will be set to SI_QUEUE.

// struct sigaction {
               // void     (*sa_handler)(int);								//老函数，不能传值
               // void     (*sa_sigaction)(int, siginfo_t *, void *); //新函数，可以传值
               // sigset_t   sa_mask;
               // int        sa_flags;
               // void     (*sa_restorer)(void);
// };
//int sigqueue(pid_t pid, int sig, const union sigval value);			//把值放在sigval这个联合体中
/*
	union sigval {
		int   sival_int;	//放整形
		void *sival_ptr;	//放指针
}; */
//用新的回到函数接受数据
void myHandle_forsigaction(int signum, siginfo_t *info, void *p)
{
	//下面两种方式获得的东西是一样的si_value.sival_int  si_int
	
	//printf("recv a sig=%d data=%d data=%d\n", signum, info->si_value.sival_int, info->si_int);
	// Teacher* t = (Teacher*)info->si_value.sival_ptr;
	// printf("t = %x\n",t);
	// if (t == NULL)
		// printf("pt is null\n");
	// else
		// printf("老师：%s\t年龄：%d\n",t->name,t->age);
	printf("%s\n",(char*)info->si_ptr);
}

int main(int argc, char *argv[])
{
	pid_t 	pid;
	int ret = 0;
	
	struct sigaction act;
	act.sa_sigaction = myHandle_forsigaction;
	//sigemptyset(&act.sa_mask);
	
	//父进程 准备接受额外数据
	act.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &act, NULL) < 0)
		ERR_EXIT("sigaction error");
		
	pid = fork();
	if (pid == -1)
	{
		printf("fork err...\n");
		return 0;
	}
	if (pid == 0)
	{
		 union sigval  mysigval;
	  // mysigval.sival_int = 222;
	  
		 // Teacher *t = (Teacher *)malloc(sizeof(Teacher));
		 // strcpy(t->name, "陈明东");
		 // t->age = 20;
	     // mysigval.sival_ptr = (void *)t;
		 // printf("tt = %x\n",t);				//奇怪啊，地址传过去了，就是发生段错误
		
	    char* ch = "陈敏东";
	   mysigval.sival_ptr = (void *)ch;		//传字符串地址过去，没问题，可以访问
		//带额外数据	
		ret  = sigqueue(getppid(), SIGQUIT, mysigval);//把SIGQUIT信号发给父进程,并且带有mysigval信息
		if (ret != 0)
		{
			printf("sigqueue .....\n");
			exit(0);
		}
		else
		{
			printf("sigqueue...successs\n");
		}
		while(1)
			pause();
	}
	else if (pid > 0)
	{
		while(1)	//这里需要一个循环，不然子进程给父进程发一个信号之后，父进程就收到之后，执行下一步，程序就结束了
			pause();//和之前那个sleep一样
	}
	return 0;
}
