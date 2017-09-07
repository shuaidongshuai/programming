#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	
	char buf[1024];
	while(1)
	{
		printf("sleep\n");
		sleep(2);
		int len = read(conn,buf,1024);
		if(0 == len)
		{
			printf("客户端退出\n");
			close(conn);
			break;
		}
		/*把读到的数据打印出来*/
		for(int i = 0;i<len;++i)
			printf("%c",buf[i]);
		printf("\n");
	}
}