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
	addfd( epoll_fd, listenfd, false);
	pid_t pid = fork();
	while(1)
	{
		printf("epoll_wait() PID=%d\n",getpid());
		num = epoll_wait(epoll_fd,events,10,-1);
		if(num < 0) return 0;
		printf("epoll_wait() over PID=%d\n",getpid());
		for(int i = 0;i<num;++i)
		{
			sockfd = events[i].data.fd;
			if(sockfd == listenfd)
			{
				if((connfd = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
					return 0;
				addfd(epoll_fd,connfd,true);
			}
			else if(events[i].events & EPOLLIN)
			{
				char buf[1024];
				/*非阻塞读*/
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
						printf("PID=%d 读错误退出\n",getpid());
						break;
					}
					else if ( bytes_read == 0 )
					{
						printf("客户端退出\n");
						close(sockfd);
						break;
					}
					index += bytes_read;
					printf("PID=%d  读到了 %d 字节\n",getpid(),bytes_read);
					printf("故意读慢一点 sleep 2s\n");
					sleep(2);
				}
				if(0 == bytes_read)
					continue;
				modfd(epoll_fd,sockfd,EPOLLIN);
				printf("PID=%d 读到的数据：",getpid());
				/*把读到的数据打印出来*/
				for(int i = 0;i<index;++i)
					printf("%c",buf[i]);
				printf("\n");
			}
		}
	}
	return 0;
}