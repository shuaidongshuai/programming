#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

int listenfd;
struct sockaddr_in peeraddr;
socklen_t peerlen = sizeof(peeraddr);
int epoll_fd;
epoll_event events[10];

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}
void addfd( int epollfd, int fd )
{
	if(setnonblocking(fd) < 0)
	{
		perror("setnonblocking 失败");
	}
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;//ET模式
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}
void addfd( int epollfd, int fd, bool one_shot)
{
	if(setnonblocking(fd) < 0)
	{
		perror("setnonblocking 失败");
	}
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;//ET模式  
	if( one_shot )
    {
        event.events |= EPOLLONESHOT;//加上 EPOLLONESHOT
    }
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}
void modfd( int epollfd, int fd, int ev )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    epoll_ctl( epollfd, EPOLL_CTL_MOD, fd, &event );
}

void *thread_hander(void *)
{
	int num,connfd,sockfd;
	while(1)
	{
		printf("epoll_wait() TID=%ld\n",pthread_self());
		num = epoll_wait(epoll_fd,events,10,-1);
		if(num < 0) return 0;
		printf("epoll_wait() over TID=%ld\n",pthread_self());
		for(int i = 0;i<num;++i)
		{
			sockfd = events[i].data.fd;
			if(sockfd == listenfd)
			{
				if((connfd = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
					return 0;
				addfd(epoll_fd,connfd);
			}
			else if(events[i].events & EPOLLIN)
			{
				char buf[1024];
				int index = 0,len = 1024,bytes_read;
				while(1)
				{
					bytes_read = read(sockfd,buf + index,len - index);
					if ( bytes_read == -1 )
					{
						if( errno == EAGAIN || errno == EWOULDBLOCK )
						{
							break;
						}
						printf("TID=%ld 读错误退出\n",pthread_self());
						break;
					}
					else if ( bytes_read == 0 )
					{
						printf("客户端退出\n");
						close(sockfd);
						return 0;
					}
					index += bytes_read;
					printf("TID=%ld  读到了 %d 字节\n",pthread_self(),bytes_read);
					printf("故意读慢一点 sleep 2s\n");
					sleep(2);
				}
				if(0 == bytes_read)
					continue;
				modfd(epoll_fd,sockfd,EPOLLIN);
				printf("TID=%ld 读到的数据：",pthread_self());
				/*把读到的数据打印出来*/
				for(int i = 0;i<index;++i)
					printf("%c",buf[i]);
				printf("\n");
			}
		}
	}
}

int main()
{
	listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(listenfd<0){
		return 0;
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		
	if((bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))<0){
		return 0;
	}
	
	if(listen(listenfd,5)<0){
		return 0;
	}
	
	/////////////////epoll////////////////////////
	epoll_fd = epoll_create(1);
	if(-1 == epoll_fd)
		return 0;
	addfd( epoll_fd, listenfd );
	
	pthread_t p1;
	pthread_t p2;
	pthread_create(&p1,NULL,thread_hander,NULL);
	pthread_create(&p2,NULL,thread_hander,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	return 0;
}