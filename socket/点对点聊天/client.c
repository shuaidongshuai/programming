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
	int sock;
	sock= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock<0){
		return 0;
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.144");

	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		return 0;
	}
	
	struct sockaddr_in localaddr;
	socklen_t addrlen = sizeof(localaddr);
	if( getsockname(sock,(struct sockaddr*)&localaddr,&addrlen)<0)//获取服务器地址和端口
		return -1;
	printf("ip = %s \nport = %d \n",inet_ntoa(localaddr.sin_addr),ntohs(localaddr.sin_port));
	
	
	pid_t pid =fork();
	if(pid == -1){
		return 0;
	}

	if(pid == 0)
	{
		char recvbuf[1024];
		while(1)
		{
			memset(recvbuf,0,sizeof(recvbuf));
			int ret = read(sock,recvbuf,sizeof(recvbuf));
			if(ret<0){
				return 0;
			}
			else if(ret == 0){
				printf("service close\n");
				break;
			}
			printf("service:");
			fputs(recvbuf,stdout);
		}
		close(sock);
		kill(getppid(),SIGUSR1);
	}
	else
	{
		signal(SIGUSR1,handler);
		char sendbuf[1024] = {0};
		while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)
		{
			write(sock,sendbuf,strlen(sendbuf));
			memset(sendbuf,0,sizeof(sendbuf));
		}
		close(sock);
	}
}





