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

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

int main(int argc,char **argv)
{
	if(argc != 3)
	{
		printf("input: IP PORT");
		return 0;
	}
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd<0){
	return 0;
	}
	
	struct sockaddr_in servaddr,client_address;
    bzero( &servaddr, sizeof( servaddr ) );
    servaddr.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &servaddr.sin_addr );
    servaddr.sin_port = htons( port );
	
	if((bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))<0){
		return 0;
	}
	
	if(listen(listenfd,5)<0){
		return 0;
	}
	
	int sockfd,cliAddrLen = sizeof(client_address);
	
	while(1)
	{
		if((sockfd = accept(listenfd,(struct sockaddr*)&client_address,&cliAddrLen))<0){
			return 0;
		}
		setnonblocking(sockfd);

		/*先读*/
		int readed,len = 0;
		char buf[1024];
		while(1)
		{
			readed = read(sockfd,buf,1024);
			if(readed < 0)
			{
				continue;
			}
			else if(readed == 0)
			{
				printf("客户端退出\n");
				close(sockfd);
				break;
			}
			len += readed;
			break;
		}
		if(0 == len)
			continue;
		// len = read(sockfd,buf,1024);
		// if(0 == len)
		// {
			// close(sockfd);
			// continue;
		// }
		
		printf("len %d\n",len);
		printf("内容：%s\n",buf);
		/*写*/
		len = write(sockfd,buf,len);
		printf("write len: = %d\n",len);
		printf("close\n");
		close(sockfd);
	}
	return 0;
}