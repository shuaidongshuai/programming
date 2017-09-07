#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "请输入：ip_address port_number\n");
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );
    
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );
    
    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );//协议域,类型,协议(默认为0)
    assert( listenfd >= 0 );
    
    int ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );
    
    ret = listen( listenfd, 5 );
    assert( ret != -1 );
    
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof( client_address );
    int fd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
     assert( ret >= 0 );
	 
    char buffer[ BUFFER_SIZE ];
	char send_buf[] = "I get a correct result\n---------------------------陈明东\n";
	memset( buffer, '\0', BUFFER_SIZE );
	int data_read;
	data_read = recv( fd, buffer, BUFFER_SIZE, 0);
	if ( data_read == -1 )
	{
		printf( "reading failed\n" );
	}
	else if(data_read == 0)
	{
		printf("客服端退出\n");
	}
	
	printf("收到的内容：\n%s\n\
	-------------------------------------------------------\n",buffer);
	send(fd,send_buf,strlen(send_buf),0);
	
	close( fd );
    close( listenfd );
    return 0;
}
/*
收到的内容：
GET / HTTP/1.1
Host: 192.168.56.142:9999
Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*\*;q=0.8
Accept-Encoding: gzip, deflate, sdch
Accept-Language: zh-CN,zh;q=0.8


		-------------------------------------------------------
*/
