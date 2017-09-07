#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
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
		else if(nread == 0)
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
		else if(nwritten == 0)
			continue;
		
		//要读的是nleft的数据 但是可能没有读到那么多的数据，所以再次循环直到读到全部数据
		bufn += nwritten;
		nleft -= nwritten;
	}	
	return count;
}

int main()
{
	int sock;
	if((sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("error");
		return 0;	
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1024);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.142");
	
	if(connect(sock,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
		printf("error");
		return 0;	
	}
	
	struct packet sendbuf;
	struct packet recvbuf;
	memset(&sendbuf,0,sizeof(sendbuf));
	memset(&recvbuf,0,sizeof(recvbuf));	
	int n;
	while(fgets(sendbuf.buf,sizeof(sendbuf.buf),stdin)!=NULL)//1.从终端读出打的字符串
	{
		n = strlen(sendbuf.buf);//获取长度
		sendbuf.len = htonl(n);//将长度编程包头（转换为网络字节序）
		writen(sock,&sendbuf, n + 4);//将包头加包体  整个发出去
		

		int ret = readn(sock,&recvbuf.len, 4 );//包头 为整形 占4个字节
		
		if(ret == -1 ){//当 读数据失败的时候
			exit(1);
		}
		if(ret < 4){//当客户端退出时  read 函数返回 0
			printf("client close\n");
			break;//跳出循环，使这个大函数返回 0  既而时这个 子进程结束
		}
		
		
		//当成功读取包头后，，下面开始正式读取数据
		n = ntohl(recvbuf.len);//读取包头长度(注意这里是网络字节序)
		ret = readn(sock, recvbuf.buf, n);
		
		if(ret == -1 ){
			exit(1);
		}
		if(ret < n){
			printf("client close\n");
			break;
		}
		
		fputs(recvbuf.buf,stdout);						//6.向终端打印
		
		memset(&sendbuf,0,sizeof(sendbuf));
		memset(&recvbuf,0,sizeof(recvbuf));		
	}
	close(sock);
	
	return 0;
}