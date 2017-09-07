#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
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
	int conn;
	if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0){
		return 0;
	}
	
	setnonblocking(conn);
	
	char buf[1024];
	int index,len;
	while(1)
	{
		printf("sleep\n");
		sleep(2);
		/*非阻塞读*/
		index = 0,len = 1024;
		while(1)
		{
			int bytes_read = read(conn,buf + index,len - index);
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
				close(conn);
				return 0;
			}
			index += bytes_read;
			printf("这次读到了 %d 字节\n",bytes_read);
		}
		/*把读到的数据打印出来*/
		for(int i = 0;i<index;++i)
			printf("%c",buf[i]);
		printf("\n");
	}
}