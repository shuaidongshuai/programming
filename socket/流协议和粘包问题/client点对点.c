//getpid()得到本身进程id,getppid()得到父进程进程id,如果已经是父进程,得到系统进程id,
#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

struct packet{
	int len;
	char buf[1024];
};

ssize_t readn(int fd, void *buf, size_t count)//根据read write 自己封装一个readn和write函数  让他必须读到自己规定的字节数
{
	size_t nleft = count;
	ssize_t nread;
	char *bufn = (char *)buf;
	
	while(nleft > 0)
	{
		if((nread = read(fd,bufn,nleft))<0)
		{
			if(errno == EINTR)//由于信号中断，没读到任何数据	#define EINTR 4 /* Interrupted system call */
			continue;
			return 0;
		}
		else if(nread == 0)//读取到末尾 
			return count - nleft;
		
		//要读的是nleft的数据 但是可能没有读到那么多的数据，所以再次循环直到读到全部数据
		bufn += nread;
		nleft -= nread;
	}	
	return count;
}
ssize_t writen(int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	ssize_t nwritten;
	char *bufn = (char *)buf;
	
	while(nleft > 0)
	{
		if((nwritten = write(fd,bufn,nleft))<0)
		{
			if(errno == EINTR)//由于信号中断，没读到任何数据
			continue;
			return 0;
		}
		else if(nwritten == 0)//如果 ==0则说明是什么也没写入, 可以继续写  
			continue;
		
		//要读的是nleft的数据 但是可能没有读到那么多的数据，所以再次循环直到读到全部数据
		bufn += nwritten;
		nleft -= nwritten;
	}	
	return count;
}


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
	servaddr.sin_port = htons(1024);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.142");

	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		return 0;
	}
	
	pid_t pid =fork();
	if(pid == -1){
		return 0;
	}
	struct packet recvbuf;
	struct packet sendbuf;
	int n;
	if(pid == 0)
	{
		while(1)
		{
			memset(&recvbuf,0,sizeof(recvbuf));
			
			int ret = readn(sock,&recvbuf.len,4);
			if(ret == -1 ){//当 读数据失败的时候
				exit(1);
			}
			if(ret < 4){//客户端退出
				printf("client close\n");
				break;
			}
			
			n = ntohl(recvbuf.len);
			ret = readn(sock,recvbuf.buf,n);
			if(ret == -1 ){//当 读数据失败的时候
				exit(1);
			}
			if(ret < n){
				printf("service close\n");
				break;
			}
			
			printf("service:");
			fputs(recvbuf.buf,stdout);
		}
		close(sock);
		kill(getppid(),SIGUSR1);
	}
	else
	{
		signal(SIGUSR1,handler);
		while(fgets(sendbuf.buf,sizeof(sendbuf.buf),stdin)!=NULL)//从终端获得将要发送的数据
		{
			n = strlen(sendbuf.buf);
			sendbuf.len = htonl(n);
			writen(sock,&sendbuf,4+n);
			memset(&sendbuf,0,sizeof(sendbuf));
		}
		close(sock);
	}
}