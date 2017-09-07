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

int main(int argc,char **argv)
{
	if(argc != 3)
	{
		printf("input: IP PORT");
	}
	
	int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
	if(sockfd<0){
	return 0;
	}
	
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	
	struct sockaddr_in servaddr;
    bzero( &servaddr, sizeof( servaddr ) );
    servaddr.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &servaddr.sin_addr );
    servaddr.sin_port = htons( port );
	
	if(-1 == connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))
	{
		perror("connect:");
		return 0;
	}
	
	/*写*/
	char buf[] = "hello cmd";
	int len = write(sockfd,buf,sizeof(buf));
	printf("write len: = %d\n",len);
	/*读*/
	while(1)
	{
		len = read(sockfd,buf,len);
		printf("len:%d\n",len);
		if(len < 0)
		{
			perror("read:");
			close(sockfd);
			break;
		}
		else if(0 == len)
		{
			printf("服务器退出\n");
			close(sockfd);
			break;
		}
	}
	printf("内容：%s\n",buf);
	return 0;
}