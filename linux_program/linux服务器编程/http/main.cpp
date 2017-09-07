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
#include "http_conn.h"

#define MAX_FD 65536
#define MAX_EVENT_NUMBER 10000

extern int addfd( int epollfd, int fd, bool one_shot );
extern int removefd( int epollfd, int fd );

void addsig( int sig, void( handler )(int), bool restart = true )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;
    if( restart )
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset( &sa.sa_mask );
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

void show_error( int connfd, const char* info )
{
    printf( "%s", info );
    send( connfd, info, strlen( info ), 0 );
    close( connfd );
}


int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

	/*忽略SIGPIPE信号*/
    addsig( SIGPIPE, SIG_IGN );

	/*创建线程池*/
    threadpool< http_conn >* pool = NULL;
    try
    {
        pool = new threadpool< http_conn >;
    }
    catch( ... )
    {
        return 1;
    }
	/*预先为每个可能的客户连接分配一个http_conn对象*/
    http_conn* users = new http_conn[ MAX_FD ];
    assert( users );
    int user_count = 0;

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );
    struct linger tmp = { 1, 0 };
    setsockopt( listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof( tmp ) );
	/*
	struct linger {
	int l_onoff;
	int l_linger;
	};为了允许SO_LINGER，应用程序应将l_onoff设为非零，将l_linger设为零或需要的超时值（以秒为单位）
	设置 l_onoff为非0，l_linger为0，则套接口关闭时TCP夭折连接，TCP将丢弃保留在套接口发送缓冲区中的任何数据并发送一个RST给对方，而不是通常的四分组终止序列，这避免了TIME_WAIT状态；
	*/

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret >= 0 );

    ret = listen( listenfd, 5 );
    assert( ret >= 0 );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create( 5 );
    assert( epollfd != -1 );
    addfd( epollfd, listenfd, false );//监听 listenfd
    http_conn::m_epollfd = epollfd;

    while( true )
    {
        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
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
				/*判断当前用户有没有达到最大*/
                if( http_conn::m_user_count >= MAX_FD )
                {
                    show_error( connfd, "Internal server busy" );
                    continue;
                }
                
                users[connfd].init( connfd, client_address );//初始化用户http对象
            }
            else if( events[i].events & ( EPOLLRDHUP | EPOLLHUP | EPOLLERR ) )
            {
                users[sockfd].close_conn();
            }
            else if( events[i].events & EPOLLIN )//读事件
            {
                if( users[sockfd].read() )
                {
                    pool->append( users + sockfd );//加入一个任务进入线程池
                }
                else
                {
                    users[sockfd].close_conn();
                }
            }
            else if( events[i].events & EPOLLOUT )//写事件
            {
                if( !users[sockfd].write() )
                {
                    users[sockfd].close_conn();
                }
            }
            else
            {}
        }
    }

    close( epollfd );
    close( listenfd );
    delete [] users;
    delete pool;
    return 0;
}
