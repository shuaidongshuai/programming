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
	servaddr.sin_port = htons(8888);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		
	if((bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))<0){
		return 0;
	}
	
	if(listen(listenfd,5)<0){
		return 0;
	}
	
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	
	
	/////////////////epoll////////////////////////
	int epoll_fd = epoll_create(1);
	if(-1 == epoll_fd)
		return 0;
	epoll_event events[10];
	int num,connfd,sockfd;
	addfd( epoll_fd, listenfd );
	while(1)
	{
		printf("epoll_wait()\n");
		num = epoll_wait(epoll_fd,events,10,-1);
		if(num < 0) return 0;
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
				printf("有读的数据到了\n");
				char buf[1024];
				/*非阻塞读*/
				int index = 0,len = 1024;
				while(1)
				{
					int bytes_read = read(sockfd,buf + index,len - index);
					if ( bytes_read == -1 )
					{
						if( errno == EAGAIN || errno == EWOULDBLOCK )
						{
							break;
						}
						return 0;
					}
					else if ( bytes_read == 0 )
					{
						printf("客户端退出\n");
						close(sockfd);
						return 0;
					}
					index += bytes_read;
					printf("这次读到了 %d 字节\n",bytes_read);
					printf("我们故意读慢一点sleep 2s\n");
					sleep(2);
				}
				/*把读到的数据打印出来*/
				for(int i = 0;i<index;++i)
					printf("%c",buf[i]);
				printf("\n");
			}
		}
	}
	return 0;
}