#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int sock;
	if((sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("error");
		return 0;	
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.141");
	
	if(connect(sock,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
		printf("error");
		return 0;
	}
	
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)//1.从终端读出打的字符串
	{
		write(sock,sendbuf,strlen(sendbuf));		//2.给服务端发送字符串
		read(sock,recvbuf,sizeof(recvbuf));			//5.读出服务端发送的字符串
		
		fputs(recvbuf,stdout);						//6.向终端打印
		
		memset(sendbuf,0,sizeof(sendbuf));
		memset(recvbuf,0,sizeof(recvbuf));		
	}
	close(sock);
	
	return 0;
}