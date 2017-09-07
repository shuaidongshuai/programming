//getpid()得到本身进程id,getppid()得到父进程进程id,如果已经是父进程,得到系统进程id,
#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include<stdlib.h>
#include<string.h>

void handler(int sig)
{
	printf("recv a sig = %d\n",sig);
	exit(1);
}

int main()
{
	int listenfd;
	listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(listenfd<0){
		return 0;
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.144");
		
	if((bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))<0){
		return 0;
	}
	
	if(listen(listenfd,SOMAXCONN)<0){
		return 0;
	}
	
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	int conn;
	if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0){
		return 0;
	}
	
	printf("IP:%s\nport:%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
	
	pid_t pid =fork();
	if(pid == -1){
		return 0;
	}
	
	//为什么把信号放在子进程中间？。。因为：子进程中没有read函数，可以明确客服端已近退出
	//read 返回 -1 读取失败  返回 0 客服端退出  write 没有 这样的功能
	if(pid == 0)//创建的子进程进行写操作
	{
		signal(SIGUSR1,handler);//信号
		char sendbuf[1024] = {0};
		while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)//从终端获得将要发送的数据
		{
			write(conn,sendbuf,strlen(sendbuf));
			memset(sendbuf,0,sizeof(sendbuf));
		}
	}
	else//父进程读
	{
		char recvbuf[1024];
		while(1)
		{
			memset(recvbuf,0,sizeof(recvbuf));
			int ret = read(conn,recvbuf,sizeof(recvbuf));
			if(ret == -1)
				return 0;
			else if( ret == 0){//当客服端退出时   跳出循环
				printf("client close \n");
				break;
			}
			printf("client:");
			fputs(recvbuf,stdout);
		}
		printf("parent close \n");
		kill(pid , SIGUSR1);//当父进程退出的时候通知子进程也退出
		exit(1);
	}
}





