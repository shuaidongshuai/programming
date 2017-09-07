/*
1.创建一个epoll句柄，参数size用来告诉内核监听的文件描述符个数，跟内存大小有关
int epoll_create(int size)
size：告诉内核监听的数目

2.控制某个epoll监控的文件描述符上的事件：注册、修改、删除。
#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
	epfd：为epoll_creat的句柄
	
	op：表示动作，用3个宏来表示：
	EPOLL_CTL_ADD(注册新的fd到epfd)，
	EPOLL_CTL_MOD(修改已经注册的fd的监听事件)，
	EPOLL_CTL_DEL(从epfd删除一个fd)；
	
	event：告诉内核需要监听的事件
	struct epoll_event {
		   uint32_t     events;      Epoll events 
		   epoll_data_t data;        User data variable 
	   };
	typedef union epoll_data {
		   void        *ptr;
		   int          fd;
		   uint32_t     u32;
		   uint64_t     u64;
	   } epoll_data_t;
	EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）
	EPOLLOUT：表示对应的文件描述符可以写
	EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）
	EPOLLERR：表示对应的文件描述符发生错误
	EPOLLHUP：表示对应的文件描述符被挂断；
	EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的
	EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
RETURN VALUE
       When successful, epoll_ctl() returns zero.  When an error occurs, epoll_ctl() returns -1 and errno is set appropriately.

	
3.等待所监控文件描述符上有事件的产生，类似于select()调用。
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)
	events：用来从内核得到事件的集合，
	maxevents：告之内核这个events有多大，这个maxevents的值不能大于创建epoll_create()时的size，
	timeout：是超时时间
	-1：阻塞
	0：立即返回，非阻塞
	>0：指定微秒
	返回值：成功返回有多少文件描述符就绪，时间到时返回0，出错返回-1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>

#define MAXLINE 80
#define IPADDR "127.0.0.1"
#define SERV_PORT 8000
#define OPEN_MAX 1024

int main()
{
	int listenfd, connfd, sockfd, nready, maxClient, efd, cliaddrLen, readLen;
	int client[OPEN_MAX];
	char buf[MAXLINE],str[20];
	
	struct sockaddr_in servaddr,cliaddr;
	struct epoll_event ep[OPEN_MAX], tep;
	
	//1
	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("创建socket失败\n");
		exit(0);
	}
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,IPADDR,&servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
	//2
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
	{
		printf("绑定失败\n");
		exit(0);
	}
	//3
	if(listen(listenfd,SOMAXCONN)<0){
		printf("监听失败\n");
		return 0;
	}
	
	for(int i = 0;i<OPEN_MAX;i++)
		client[i] = -1;
	maxClient = -1;
	
	//一
	if((efd = epoll_create(OPEN_MAX)) == -1)//获取epoll句柄,这个句柄指向内核中创建的红黑树的根节点
	{
		printf("创建epoll句柄失败\n");
		exit(0);
	}
	
	//二
	tep.events = EPOLLIN;
	tep.data.fd = listenfd;
	if(epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep) == -1)// 为监听套接字设置 监听事件
	{
		printf("epoll监听listenfd失败\n");
		exit(0);
	}
	
	while(1)
	{
		/* 阻塞监听*/
		nready = epoll_wait(efd,ep,OPEN_MAX,-1);//1.从内核得到的事件集合，2.告诉内核这个集合多大，3.超时时间
		if(nready == -1)
		{
			printf("epoll wait error");
			exit(0);
		}
		
		for(int i = 0 ;i < nready; i++)
		{
			if(!(ep[i].events & EPOLLIN))
				continue;//如果这个事件没有发生读事件，则继续下一个
			
			/*处理监听套接字的消息，也就是处理客服端连接请求*/
			if(ep[i].data.fd == listenfd)
			{
				cliaddrLen = sizeof(cliaddr);
				if((connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrLen)) < 0)
				{
					printf("accept error\n");
					exit(0);
				}
				printf("收到一个来自 %s:%d 消息\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));
				
				for(int i = 0;i<OPEN_MAX;i++)
				{
					if(client[i] < 0)
					{
						client[i] = connfd;
						if(i == OPEN_MAX)
						{
							printf("文件描述符创建到最大了,client 太多了\n");
							return 0;
						}
						if(i > maxClient)
							maxClient = i;
						break;
					}
				}
				/*把连接上来的客服端加入到 epoll 的红黑树中*/
				tep.events = EPOLLIN;
				tep.data.fd = connfd;
				if(epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep) == -1)
				{
					printf("epoll add connfd error\n");
					return 0;
				}
			}
			else//下面是处理客服端发送的数据
			{
				sockfd = ep[i].data.fd;
				readLen = read(sockfd,buf,MAXLINE);
				
				if(readLen == -1)
				{
					printf("socket read error\n");
				}
				else if(readLen == 0)
				{
					for(int j = 0;j < maxClient; j++)
					{
						if(client[j] == sockfd)
						{
							printf("client[%d] closed connection\n",j);
							client[j] = -1;	//read == 0 说明客服端退出了，那么回收资源
							break;
						}
					}
					if(epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL) == -1)//在epoll中回收资源
					{
						printf("epoll del error\n");
						return 0;
					}
					close(sockfd);
				}
				else//到这个地方，客服端的数据才正真到达
				{
					buf[readLen] = '\0';
					printf("client:%s",buf);
					char sendBuf[100] = "服务器收到：";
					strcat(sendBuf,buf);
					write(sockfd,sendBuf,strlen(sendBuf));
				}
			}
		}
	}
	close(listenfd);
	close(efd);
	return 0;
}






