#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//改变的程序
int do_service(int conn)
{
	char recvbuf[1024];
	while(1)
	{
		memset(recvbuf,0,sizeof(recvbuf));
		int ret = read(conn,recvbuf,sizeof(recvbuf));
		
		if(ret == 0){//当客户端退出时  read 函数返回 0
			printf("client close\n");
			break;//跳出循环，使这个大函数返回 0  既而时这个 子进程结束
		}
		else if(ret == -1 ){//当 读数据失败的时候
			break;
		}
		
		fputs(recvbuf,stdout);
		write(conn,recvbuf,ret);
	}
	return 0;
}

int main()
{
	int listenfd;
	if((listenfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("error");
		return 0;
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.141");
	
	int on = 1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))){	
		return 0;
	}
	
	if(bind(listenfd,(struct sockaddr *)&servaddr , sizeof(servaddr))<0){
		printf("error");
		return 0;
	}
	
	if(listen(listenfd,SOMAXCONN)<0){ 
		printf("error");
		return 0;		
	}
	 //以上完成了  初始化服务器。。使服务器处于监听状态
	 
	 
	  struct sockaddr_in peeraddr;
	  socklen_t peerlen = sizeof(peeraddr);  
	  int conn;
	  while(1)
	  {
		if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0){
		printf("error");
		return 0;
	  }
		  //运行到这  就说明 完成了三次握手
		  
		  printf("IP:%s\nport:%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
		  
		  pid_t pid = fork();//创建子进程
		  if(pid == 0)// 子进程   给每一个客服端专门创建一个子进程
		  {
			  close(listenfd);//子进程关闭监听套接字  不需要监听其他的客服端了   也不能接收了
			  do_service(conn);
			  return 0;   //客服端关闭了 子进程就没有存在的必要了
		  }
		  else
			  close(conn);//父进程  关闭已连接套接字，就可以监听其他客服端的请求了
	  }	  	
	return 0;
}
