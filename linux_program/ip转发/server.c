#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

#include "locker.h"
#include "threadpool.h"

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

void addfd( int epollfd, int fd, bool one_shot )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    if( one_shot )
    {
        event.events |= EPOLLONESHOT;//如果在处理写成当前的SOCKET后不再重新注册相关事件，那么这个事件就不再响应了或者说触发了。
    }
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}

class Server
{
public:
	char buf[1024];
	int sockfd;
	void init(int fd)
	{
		sockfd = fd;
	}
	bool readdata()
	{
		memset(buf,0,sizeof(buf));
		
		int nread = 0;
		int n;
		while ((n = read(sockfd, buf + nread, 1024)) > 0) 
		{
			nread += n;
		}
		if (nread == -1 && errno != EAGAIN) 
		{
			close(sockfd);
			return false;
		}
		if (nread == 0) 
		{
			printf("客服端退出\n");
			return false;
		}
		buf[nread] = 0;
		return true;
	}
	void process()
	{
		printf("%s\n",buf);
	}
	void close_conn()
	{
		close(sockfd);
	}
};

int main(int argc,char **argv)
{
	if(argc != 3)
	{
		printf("请输入 ip port\n");
		return 0;
	}
	int listenfd,connfd;
	struct sockaddr_in servaddr, cliaddr;
	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("创建socket失败\n");
		exit(0);
	}
	
	int reuse = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        return -1;
    }
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2]));
	
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
	{
		printf("绑定失败\n");
		exit(0);
	}
	
	if(listen(listenfd,5) < 0)
	{
		printf("监听失败\n");
		exit(0);
	}
	
	threadpool<Server> *pool = new threadpool<Server>;
	Server *users = new Server[1024];
	
	epoll_event events[1024];
	int epollfd;
	if((epollfd = epoll_create(1024)) == -1)
	{
		printf("epoll_create error\n");
		exit(0);
	}
	addfd( epollfd, listenfd, false );//监听 listenfd
	
	while( true )
    {
        int number = epoll_wait( epollfd, events, 1024, -1 );
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            if( sockfd == listenfd )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                if ( connfd < 0 )
                {
                    printf( "errno is: %d\n", errno );
                    continue;
                }
				printf("connfd : %d--------------------------\n",connfd);
				users[connfd].init(connfd);
				addfd( epollfd, connfd, false );
            }
            else if( events[i].events & ( EPOLLRDHUP | EPOLLHUP | EPOLLERR ) )
            {
                users[sockfd].close_conn();
            }
            else if( events[i].events & EPOLLIN )//读事件
            {
                if( users[sockfd].readdata() )
                {
                    pool->append( users + sockfd );//加入一个任务进入线程池
                }
                else
                {
                    users[sockfd].close_conn();
                }
            }
        }
    }

    close( epollfd );
    close( listenfd );
    delete [] users;
    delete pool;
	return 0;
}