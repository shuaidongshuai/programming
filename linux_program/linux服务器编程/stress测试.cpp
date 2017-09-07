#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

#include <iostream>
#include <fstream>
using namespace std;

#define MAX_EVENT_NUMBER 65536
//static const char* request = "GET /list.html HTTP/1.1\r\nConnection: keep-alive\r\n\r\nxxxxxxxxxxxx";
static const char* request = "GET /list.html HTTP/1.1\r\nConnection: close\r\n\r\nxxxxxxxxxxxx";
//static const char* request = "GET / HTTP/1.1 User-Agent: Wget/1.17.1 (linux-gnu) Accept: */* Accept-Encoding: identity Host: www.baidu.com Connection: Keep-Alive\r\n\r\nxxxxxxxxxxxx";

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

bool write_nbytes( int sockfd, const char* buffer, int len )
{
    int bytes_write = 0;
    while( 1 ) //一定要写完
    {
        bytes_write = send( sockfd, buffer, len, 0 );
        if ( bytes_write == -1 )
        {   
            return false;
        }   
        else if ( bytes_write == 0 ) 
        {   
            return false;
        }   
        len -= bytes_write;
        buffer = buffer + bytes_write;
        if ( len <= 0 )
			break;
    }
	printf( "writed out %d bytes to socket %d\n", bytes_write, sockfd );
	return true;
}

bool read_once( int sockfd, char* buffer, int len )
{
    int bytes_read = 0;
    memset( buffer, '\0', len );
	while(1)
	{
		bytes_read = recv( sockfd, buffer, len, 0 );
		cout<<"bytes_read "<<bytes_read<<endl;
		if ( bytes_read == -1 )
		{
			printf("erron:%s\n",strerror(errno));
			return false;
		}
		else if ( bytes_read == 0 )
		{
			break;
		}
	}
    return true;
}

void addfd( int epoll_fd, int fd )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLOUT | EPOLLET | EPOLLERR;//1.描述符可以写 2.et模式 3.描述符发生错误   注意：这里out，因为需要先写http请求给server
    epoll_ctl( epoll_fd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}
void close_conn( int epoll_fd, int fd )
{
    epoll_ctl( epoll_fd, EPOLL_CTL_DEL, fd, 0 );//4.告诉内核需要监听什么事
    if(close( fd ))
	{
		printf("close error:%s\n",strerror(errno));
	}
}

/*创建socket，连接服务器，并加入到epoll    num:发起连接的个数*/
void start_conn( int epoll_fd, int num, const char* ip, int port )
{
    int ret = 0;
    struct sockaddr_in address;
	struct hostent *hp;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
	
	/* 用户可能传入www.google.com */
	unsigned long inaddr = inet_addr(ip);//将一个点分十进制的IP转换成一个长整数型数
    if (inaddr != INADDR_NONE)
		memcpy(&address.sin_addr, &inaddr, sizeof(inaddr));//由于已经是10进制了，所以不需要用inet_pton这个函数了，直接copy
    else
    {
        hp = gethostbyname(ip);//返回对应于给定主机名的包含主机名字和地址信息的hostent结构指针
        if (hp == NULL)
            return;
        memcpy(&address.sin_addr, hp->h_addr, hp->h_length);
    }
    //inet_pton( AF_INET, ip, &address.sin_addr );//IP地址转换函数，可以在将IP地址在“点分十进制”和“二进制整数”之间转换 并放到第三个参数中
    address.sin_port = htons( port );

    for ( int i = 0; i < num; ++i )
    {
        //sleep( 1 );
        int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
        //printf( "create socket%d\n", sockfd);
        if( sockfd < 0 )
        {
            continue;
        }
        if (  connect( sockfd, ( struct sockaddr* )&address, sizeof( address ) ) == 0  )
        {
            printf( "build connection %d\n", sockfd );
            addfd( epoll_fd, sockfd );
			//usleep(1000);
        }
    }
}

int main( int argc, char* argv[] )
{
	if(argc != 4)
	{
		printf("请输出入：IP PORT NUM\n");
		return 0;
	}
    int epoll_fd = epoll_create( MAX_EVENT_NUMBER );//1.用来告诉内核这个监听的数目一共有多大
	int num = atoi( argv[ 3 ] );
    start_conn( epoll_fd, num, argv[1],  atoi( argv[ 2 ] ));
    epoll_event events[ MAX_EVENT_NUMBER ];
    char buffer[ 2048 ];
    while ( 1 )
    {
        int fds = epoll_wait( epoll_fd, events, MAX_EVENT_NUMBER, -1 );//1.epoll_fd 2.用来从内核得到事件的集合 3.每次能处理的最大事件数 4.超时时间 毫秒，0会立即返回
        for ( int i = 0; i < fds; i++ )
        {   
            int sockfd = events[i].data.fd;
            if ( events[i].events & EPOLLIN )//读事件
            {   
                if ( ! read_once( sockfd, buffer, 2048 ) )
                {
                    close_conn( epoll_fd, sockfd );
                }
				//用C++的流,输出到文件中
				//ofstream outfile("./outfile",ios::app);
				//outfile<<buffer<<endl;
				
				close_conn( epoll_fd, sockfd );
				//cout<<"-------------------------------"<<num<<endl;
				if(--num == 0)
					return 0;
			}
            else if( events[i].events & EPOLLOUT )//写事件
            {
                if ( ! write_nbytes( sockfd, request, strlen( request ) ) )
                {
                    close_conn( epoll_fd, sockfd );
                }
                struct epoll_event event;
                event.events = EPOLLIN | EPOLLET | EPOLLERR;
                event.data.fd = sockfd;
                epoll_ctl( epoll_fd, EPOLL_CTL_MOD, sockfd, &event );//把写事件改为读事件
            }
            else if( events[i].events & EPOLLERR )//描述符有错误
            {
                close_conn( epoll_fd, sockfd );
            }
        }
    }
}
/*
对于LT 模式，如果注册了EPOLLOUT，只要该socket可写(发送缓冲区)未满，那么就会触发EPOLLOUT。
对于ET模式，如果注册了EPOLLOUT,只有当socket从不可写变为可写的时候，会触发EPOLLOUT。
*/

