/*
#include <poll.h>
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
struct pollfd {
int fd;  文件描述符
short events;  监控的事件
short revents;  监控事件中满足条件返回的事件
};
POLLIN普通或带外优先数据可读,即POLLRDNORM | POLLRDBAND
POLLRDNORM-数据可读
POLLRDBAND-优先级带数据可读
POLLPRI 高优先级可读数据
POLLOUT普通或带外数据可写
POLLWRNORM-数据可写
POLLWRBAND-优先级带数据可写
POLLERR 发生错误
POLLHUP 发生挂起
POLLNVAL 描述字不是一个打开的文件

nfds 监控数组中有多少文件描述符需要被监控

timeout 毫秒级等待
-1：阻塞等，#define INFTIM -1 Linux中没有定义此宏
0：立即返回，不阻塞进程
>0：等待指定毫秒数，如当前系统时间精度不够毫秒，向上取值
如果不再监控某个文件描述符时，可以把pollfd中，fd设置为-1，poll不再监控此
pollfd，下次返回时，把revents设置为0。

返回值:
>0：数组fds中准备好读、写或出错状态的那些socket描述符的总数量；
==0：数组fds中没有任何socket描述符准备好读、写，或出错；此时poll超时，超时时间是timeout毫秒；
换句话说，如果所检测的 socket描述符上没有任何事件发生的话，那么poll()函数会阻塞timeout所指定的毫秒时间长度之后返回，
如果timeout==0，那么 poll() 函数立即返回而不阻塞，如果timeout== -1，那么poll() 函数会一直阻塞下去，
直到所检测的socket描述符上的感兴趣的事件发 生是才返回，如果感兴趣的事件永远不发生，那么poll()就会永远阻塞下去；
-1：  poll函数调用失败，同时会自动设置全局变量errno；

如果待检测的socket描述符为负值，则对这个描述符的检测就会被忽略，
也就是不会对成员变量events进行检测，在events上注册的事件也会被忽略，
poll()函数返回的时候，会把成员变量revents设置为0，表示没有事件发生；

struct pollfd {
	   int   fd;          file descriptor 
	   short events;      requested events 
	   short revents;    returned events 
   };
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>
#include <unistd.h>
#define MAXLINE 80
#define SERV_PORT 8000
#define OPEN_MAX 1024	//打开的最大文件个数  可以用ulimit -n 1024来修改
#define IPADDR "127.0.0.1"
int main()
{
	int n, maxClient, clientfd, sockfd, nready;
	struct pollfd client[OPEN_MAX	];
	struct sockaddr_in cliaddr,servaddr;
	int cliaddrlen;
	char buf[MAXLINE],str[20];
	
	//1
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	 /*一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。*/
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        return -1;
    }
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,IPADDR,&servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
	//2
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	//3
	listen(sockfd,SOMAXCONN);//用SOMAXCONN则由系统确定
	
	client[0].fd = sockfd;
	client[0].events = POLLRDNORM;/* sockfd监听普通读事件*/
	
	/* 用-1初始化client[]里剩下元素*/
	for(int i = 1;i<OPEN_MAX;i++)
		client[i].fd = -1;
	
	maxClient = 0;//用于记录当前已连接的客服端个数
	
	while(1)
	{
		printf("1nready = %d\n",nready);
		nready = poll(client,maxClient+1,-1);/* -1	阻塞*///返回产生事件的个数
		printf("2nready = %d\n",nready);
		if(client[0].revents & POLLRDNORM)/* 有客户端链接请求*///监听到sockfd中有读事件
		{
			cliaddrlen = sizeof(cliaddr);
			clientfd = accept(sockfd,(struct sockaddr*)&cliaddr,&cliaddrlen);//处理一个正在等待的clientfd
			printf("收到一个来自 %s:%d 消息\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));
			
			/*找到client[]中空闲的位置，存放accept返回的clientfd */
			for(int i = 1;i<OPEN_MAX;i++)
			{
				if(client[i].fd<0)
				{
					client[i].fd = clientfd;
					client[i].events = POLLRDNORM; /* 设置刚刚返回的connfd，监控读事件*/
					if(i>maxClient)
						maxClient = i;
					printf("ii = %d\n",i);
					break;
				}
			}

			if(maxClient == OPEN_MAX)
			{
				printf("客服端太多了\n");
				exit(0);
			}
			
			//在访问量不大的时候可以不要下面判断，如果访问量大，那么就需要先处理客服端的请求，然后再处理数据
			 if(nready != 1)//不等于1说明还有未处理的事件（可能这个事件就是三次握手，也可能是别的clientfd发生了读事件）
				continue;
		}
		//开始处理每个客服端的请求
		for(int i = 1;i<=maxClient;i++)
		{
			clientfd = client[i].fd;
			if(clientfd < 0)
				continue;
			if(client[i].revents & POLLRDNORM)//判断某个clientfd是否发生读事件**********************
			{
				if((n = read(clientfd,buf,MAXLINE)) < 0)
				{
					if(errno == ECONNRESET)/* 当收到RST标志时*/
					{
						/* connection reset by client */
						printf("client[%d] aborted connection\n", i);
						close(clientfd);
						client[i].fd = -1;
					}
					else
					{
						printf("client读错误\n");
						exit(0);
					}
				}
				else if(0 == n)
				{
					/* connection closed by client */
					printf("client[%d] closed connection\n", i);
					close(clientfd);
					client[i].fd = -1;
				}
				else
				{
					buf[n] = '\0';
					printf("buf = %s",buf);
					write(clientfd,buf,n);//把读到的数据返回给客服端
				}
				   if (--nready <= 0)//加上只是节约一点时间，因为只发生了nready个事件   多几次循环只是浪费一点罢了
					   break; /* no more readable descriptors */
			}
		}
	}
	return 0;
}

/*
const char *inet_ntop(int af, const void *src,
                             char *dst, socklen_t size);
将点二进制转化为点分十进制
RETURN VALUE
       On success, inet_ntop() returns a non-null pointer  to  dst.


*/