#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#define MAXLINE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8787

#define max(a,b) (a > b) ? a : b

static void handle_recv_msg(int sockfd, char *buf) 
{
	printf("client recv msg is:%s\n", buf);
	sleep(5);
	write(sockfd, buf, strlen(buf) +1);
}

static void handle_connection(int sockfd)
{
	char sendline[MAXLINE],recvline[MAXLINE];
	int maxfdp,stdineof;
	fd_set readfds;
	int n;
	struct timeval tv;
	int retval = 0;

	while (1) {

		FD_ZERO(&readfds);//把文件描述符集合里所有位清0
		FD_SET(sockfd,&readfds);//把文件描述符集合里fd位置1
		maxfdp = sockfd;

		tv.tv_sec = 5;
		tv.tv_usec = 0;

		retval = select(maxfdp+1,&readfds,NULL,NULL,&tv);

		if (retval == -1) {
			return ;
		}
		if (retval == 0) {
			printf("client timeout.\n");
			continue;
		}

		if (FD_ISSET(sockfd, &readfds)) {//测试文件描述符集合里fd是否置1
			n = read(sockfd,recvline,MAXLINE);
			if (n <= 0) {
				fprintf(stderr,"client: server is closed.\n");
				close(sockfd);
				FD_CLR(sockfd,&readfds);
				return;
			}
			handle_recv_msg(sockfd, recvline);
		}
	}
}

int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));//置字节字符串前n个字节为零且包括‘\0’。
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET,IPADDRESS,&servaddr.sin_addr);//IP地址转换函数，可以在将IP地址在“点分十进制”和“二进制整数”之间转换,将“点分十进制” －> “二进制整数”

	int retval = 0;
	retval = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if (retval < 0) {
		fprintf(stderr, "connect fail,error:%s\n", strerror(errno));
		return -1;
	}

	printf("client send to server .\n");
	write(sockfd, "hello server", 32);

	handle_connection(sockfd);

	return 0;
}
/*
int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);
	nfds: 监控的文件描述符集里最大文件描述符加1，因为此参数会告诉内核检测前多少个文件描述符的状态
	readfds：监控有读数据到达文件描述符集合，传入传出参数
	writefds：监控写数据到达文件描述符集合，传入传出参数
	exceptfds：监控异常发生达文件描述符集合,如带外数据到达异常，传入传出参数
	timeout：定时阻塞监控时间，3种情况
	1.NULL，永远等下去
	2.设置timeval，等待固定时间
	3.设置timeval里时间均为0，检查描述字后立即返回，轮询


struct timeval {
long tv_sec;  seconds 
long tv_usec;  microseconds 

RETURN VALUE
	>0：就绪描述字的正数目
	-1：出错
	0 ：超时
};


inet_pton：将“点分十进制” －> “二进制整数”
int inet_pton(int af, const char *src, void *dst);
	这个函数转换字符串到网络地址，第一个参数af是地址簇，第二个参数*src是来源地址，第三个参数* dst接收转换后的数据。
	inet_pton 是inet_addr的扩展，支持的多地址族有下列：
	af = AF_INET
	src为指向字符型的地址，即ASCII的地址的首地址（ddd.ddd.ddd.ddd格式的），函数将该地址转换为in_addr的结构体，并复制在*dst中。
	af = AF_INET6
	src为指向IPV6的地址，函数将该地址转换为in6_addr的结构体，并复制在*dst中。
	如果函数出错将返回一个负值，并将errno设置为EAFNOSUPPORT，如果参数af指定的地址族和src格式不对，函数将返回0。

*/