#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("请输入 ip port\n");
		return 0;
	}
	
	int sockfd;
	struct sockaddr_in servaddr;
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		printf("创建socket失败\n");
		return 0;
	}
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2]));
	
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
	{
		printf("连接失败\n");
		return 0;
	}
	char str[1024];
	while(cin>>str)
	{
		write(sockfd, str, strlen(str));
		cout<<str<<endl;
		memset(str,0,1024);
	}
	
	close(sockfd);
	sleep(3);
	return 0;
}