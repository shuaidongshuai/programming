//TCP客服/服务器模型
//回射客户/服务器
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
	int listenfd;
	if((listenfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){//创建一个  监听socket
		printf("error");
		return 0;
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;//指定协议族
	servaddr.sin_port = htons(5188);//指定端口
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.141");//指定IP
	
	int on = 1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))){	//关闭服务器的时候不能马上启动，要TIME_wait 用来这个函数就可以重新使用地址不等待
		return 0;
	}
	
	if(bind(listenfd,(struct sockaddr *)&servaddr , sizeof(servaddr))<0){//用于绑定IP地址和端口号到socket
		printf("error");
		return 0;
	}
	
	if(listen(listenfd,SOMAXCONN)<0){ 
		printf("error");
		return 0;		
	}
	 
	 struct sockaddr_in peeraddr;//定义一个对方的地址
	  socklen_t peerlen = sizeof(peeraddr);//定义对方的地址长度
	  
	  int conn;//accept要返回一个新的套接字(已连接套接字)(listendfd是被动套接字，conn为主动套接字(conn（已连接socket）就相当于客服端的socket))
	  if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0){//从完成连接队列返回第一个连接，如果已完成连接队列为空，则阻塞
		printf("error");
		return 0;			  
	  }
	  
	  printf("IP:%s\nport:%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
	  
	  char recvbuf[1024];
	  while(1)
	  {
		  memset(recvbuf,0,sizeof(recvbuf));
		  
		  int ret = read(conn,recvbuf,sizeof(recvbuf));//3.读出客服端发过来的字符串
		  write(conn,recvbuf,ret);						//4.把读出来的字符串返回给客服端
		  
		  fputs(recvbuf,stdout);						//6.把收到的字符串打印出来

		  
	  }
	  
	return 0;
}
/* 
(1)listen() 函数的主要作用就是将套接字( sockfd )变成被动的连接监听套接字（被动等待客户端的连接），
至于参数 backlog 的作用是设置内核中连接队列的长度

(1)listen()只是对端口的同时最大连接数做一个限制，
而且只有socket()创建socket描述符时type为SOCK_STREAM，即创建有链接通信时才能用到。
比如listen(sock_fd,100)即是限定同时来连接的数量不能超过101.有一个可以马上处理，100个放入某个队列，等待处理。
超过的连接请求会收到一个连接错误的返回。 */
