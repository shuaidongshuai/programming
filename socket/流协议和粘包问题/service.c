//TCP是流协议，并不能保证对方一次性接收确定长度
//也就是说不能保证read一次接收到的就是 对方发送的长度（尽管read函数  第三个参数里面填的是接收1024字节）
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
struct packet{
	int len;
	char buf[1024];
};

ssize_t readn(int fd, void *buf, size_t count)//根据read write 自己封装一个readn和write函数  让他必须读到自己规定的字节数
{
	size_t nleft = count;
	ssize_t nread;
	char *bufn = (char *)buf;
	
	while(nleft > 0)
	{
		if((nread = read(fd,bufn,nleft))<0)
		{
			if(errno == EINTR)//由于信号中断，没读到任何数据	#define EINTR 4 /* Interrupted system call */
			continue;
			return 0;
		}
		else if(nread == 0)//读取到末尾   read返回0时，表示客服端退出
			return count - nleft;//正常的话  == count - 0   相当于返回 需要读取的数据
		
		//要读的是nleft的数据 但是可能没有读到那么多的数据，所以再次循环直到读到全部数据
		bufn += nread;
		nleft -= nread;//读完 10字节 -10  读完全部 就为0 了
	}	
	return count;
}
ssize_t writen(int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	ssize_t nwritten;
	char *bufn = (char *)buf;
	
	while(nleft > 0)
	{
		if((nwritten = write(fd,bufn,nleft))<0)
		{
			if(errno == EINTR)//由于信号中断，没读到任何数据
			continue;
			return 0;
		}
		else if(nwritten == 0)//如果 ==0则说明是什么也没写入, 可以继续写  
			continue;
		
		//要读的是nleft的数据 但是可能没有读到那么多的数据，所以再次循环直到读到全部数据
		bufn += nwritten;
		nleft -= nwritten;
	}	
	return count;
}

int do_service(int conn)
{
	struct packet recvbuf;
	int n;
	while(1)
	{
		memset(&recvbuf,0,sizeof(recvbuf));
		int ret = readn(conn,&recvbuf.len,4 );//包头 为整形 占4个字节
		
		if(ret == -1 ){//当 读数据失败的时候
			exit(1);
		}
		if(ret < 4){//当客户端退出时  read 函数返回 0
			printf("client close\n");
			break;//跳出循环，使这个大函数返回 0  既而时这个 子进程结束
		}
		
		//当成功读取包头后，，下面开始正式读取数据
		n = ntohl(recvbuf.len);//读取包头长度(注意这里是网络字节序)
		ret = readn(conn, recvbuf.buf, n);
		
		if(ret == -1 ){
			exit(1);
		}
		if(ret < n ){
			printf("client close\n");
			break;
		}
		
		fputs(recvbuf.buf,stdout);
		writen(conn,&recvbuf, n + 4 );
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
	servaddr.sin_port = htons(1024);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.142");
	
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
