#include<sys/types.h>
#include<sys/socket.h>						// 1 2 socket	bind	listen	accept	connect
#include<string.h>							// 3 bzero
#include<netinet/in.h>
#include<arpa/inet.h>						//2 4 5 inet_aton
#include<unistd.h>							// 6 read close
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include <netdb.h> 							// 10 gethostbyname
int main(int argc,char **argv)
{
	int sockfd;
	char buffer[1024];
	struct sockaddr_in server_addr;
	struct hostent *host;
	if(argc!=2)
	{
		printf("error\n");
		return 1;
	}
	//使用hostent 咨询host名字
	if((host=gethostbyname(argv[1]))==NULL)
	{
		printf("gethostname error\n");
		return 1;
	}
	//客服程序开始建立 sockfd 描述符
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	//客服程序填充服务端资料
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(3333);
	server_addr.sin_addr=*((struct in_addr *)host->h_addr); // IP地址
	//客服程序 发出 连接 请求
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
	{
		printf("connect error:%s\n",strerror(errno));
		return 1;
	}
	//成功连接
	printf("Please input char :\n");
	//发送数据
	fgets(buffer,1024,stdin); 
	write(sockfd,buffer,strlen(buffer)); 
	/* 结束通讯 */ 
	close(sockfd); 
	return 1;
}