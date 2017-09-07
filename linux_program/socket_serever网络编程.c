#include<sys/types.h>
#include<sys/socket.h>						// 1 2 socket	bind	listen	accept
#include<string.h>							// 3 bzero
#include<netinet/in.h>
#include<arpa/inet.h>						//2 4 5 inet_aton
#include<unistd.h>							// 6 read close
#include<errno.h>
#include<stdio.h>

int main()
{
	int sockfd,new_fd;
	struct sockaddr_in server_addr,client_addr;
	int sin_size,nbytes;
	char buffer[1024];
	
	//开始建立sockfd描述符
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)//AF_INET:IPV4;SOCK_STREAM:TCP,第三个参数一般为0
	{
		printf("socket error:%s\n\a",strerror(errno));
		return 1;
	}
	// 服务器端填充 sockaddr 结构
	bzero(&server_addr,sizeof(struct sockaddr_in));//置字节字符串前n个字节为零且包括‘\0’。
	server_addr.sin_family=AF_INET;				//	Internet
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);// (将本机器上的long数据转化为网络上的long数据)和任何主机通信  //INADDR_ANY 表示可以接收任意IP地址的数据，即绑定到所有的IP
	server_addr.sin_port=htons(3333);			// (将本机器上的short数据转化为网络上的short数据)端口号
	//捆绑sockfd描述符到IP地址
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
	{
		printf("bind error:%s\n\a",strerror(errno));
		return 1;
	}
	//设置连接的最大客服端数
	if(listen(sockfd,5)==-1)
	{
		printf("listen error:%s\n\a",strerror(errno));
		return 1;
	}
	while(1)
	{
		sin_size=sizeof(struct sockaddr_in); 
		if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)	//服务器阻塞，直到客服程序建立连接
		{
			printf("accept error:%s\n",strerror(errno));
			return 1;
		}
		printf("server get connection from %s\n",inet_ntoa(client_addr.sin_addr));		// 把32位数转化为 字符串
		if((nbytes=read(new_fd,buffer,1024))==-1)										//读取数据
		{
			printf("read error:%s\n",strerror(errno));
			return 1;
		}
		buffer[nbytes]='\0';
		printf("server receive %s\n",buffer);
	//这个通讯已近结束
	close(new_fd);
	}
	close(sockfd);
	return 1;
}