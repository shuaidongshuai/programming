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
	int listenfd;
	listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(listenfd<0){
		return 0;
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1024);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.142");
		
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
	struct packet recvbuf;
	struct packet sendbuf;
	int n;
	if(pid == 0)//创建的子进程进行写操作
	{
		signal(SIGUSR1,handler);//信号量
		while(fgets(sendbuf.buf,sizeof(sendbuf.buf),stdin)!=NULL)//从终端获得将要发送的数据
		{
			n = strlen(sendbuf.buf);
			sendbuf.len = htonl(n);			
			writen(conn,&sendbuf,4+n);
			memset(&sendbuf,0,sizeof(sendbuf));
		}
	}
	else//父进程读
	{
		while(1)
		{
			memset(&recvbuf,0,sizeof(recvbuf));
			
			int ret = readn(conn,&recvbuf.len,4);
			if(ret == -1 ){//当 读数据失败的时候
				exit(1);
			}
			if(ret < 4){//客户端退出
				printf("client close\n");
				break;
			}
			
			n = ntohl(recvbuf.len);
			ret = readn(conn,recvbuf.buf,n);
			if(ret == -1 ){//当 读数据失败的时候
				exit(1);
			}
			if(ret < n){//客户端退出
				printf("client close\n");
				break;
			}
			
			printf("client:");
			fputs(recvbuf.buf,stdout);
		}
		
		printf("parent close \n");
		kill(pid , SIGUSR1);//当父进程退出的时候通知子进程也退出
		exit(1);
	}
}