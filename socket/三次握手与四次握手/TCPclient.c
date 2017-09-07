#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

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
		else if(nread == 0)
			return count - nleft;
		
		//要读的是nleft的数据 但是可能没有读到那么多的数据，所以再次循环直到读到全部数据
		bufn += nread;
		nleft -= nread;
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
		else if(nwritten == 0)
			continue;
		
		//要读的是nleft的数据 但是可能没有读到那么多的数据，所以再次循环直到读到全部数据
		bufn += nwritten;
		nleft -= nwritten;
	}	
	return count;
}

/*
	ssize_t recv(int sockfd, void *buf, size_t len, int flags);
 MSG_PEEK
              This flag causes the receive operation to return data from the beginning of the  receive  queue  without
              removing that data from the queue.  Thus, a subsequent receive call will return the same data.	*///读完后不会清空缓冲区
ssize_t recv_peek(int sockfd, void *buf, size_t len)//自己封装一个 recv 让他的标志位 MSG_PEEK 函数
{
	while(1)
	{
		int ret = recv(sockfd,buf,len,MSG_PEEK);//设置标志位后读取后不清除缓冲区
		if(ret == -1 && errno == EINTR)//被中断的时候
		continue;
		return ret;//返回读到的长度
	}
}
/* 在readline函数中，我们先用recv_peek”偷窥“ 一下现在缓冲区有多少个字符并读取到bufp，然后查看是否存在换行符'\n'。如果存在，则使用readn连

通换行符一起读取（清空缓冲区）；如果不存在，也清空一下缓冲区, 且移动bufp的位置，回到while循环开头，再次窥看。注意，当我们调用readn读

取数据时，那部分缓冲区是会被清空的，因为readn调用了read函数。还需注意一点是，如果第二次才读取到了'\n'，则先用count保存了第一次读取的

字符个数，然后返回的ret需加上原先的数据大小。 */		
ssize_t readline(int sockfd, void *buf, size_t maxline)
{
	int ret ;
	int nread;
	char *bufp = (char *)buf;
	int nleft = maxline;
	int count = 0;//用来保存读到的数据大小
	while(1)
	{
		ret = recv_peek(sockfd,bufp,nleft);//把数据读到bufp中.....按理来说要读 nleft个字节 但是不一定读那么多
		if(ret < 0)//返回小于0表示失败
			return ret;
		else if( ret == 0)//返回0表示对方关闭连接了
			return ret;	
		
		nread = ret;	//把 读到 字节数 记录下来
		int i;
		for(i=0;i<nread;i++)
		{
			if(bufp[i] == '\n')//定位到 \n 
			{
				ret = readn(sockfd,bufp,i+1);//读取 \n  之前所有的内容
				if(ret != i+1)
					exit(EXIT_FAILURE);
				return ret + count;
			}
		}
		if(nread > nleft)//正常的话nread 是 <= nleft
			exit(EXIT_FAILURE);
			
			nleft -= nread;
			count +=nread;
	}
}

void echo_cli(int sock)
{
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)//1.从终端读出打的字符串
	{
		//writen(sock,sendbuf, strlen(sendbuf));
		//修改为：分两次发送
		write(sock,sendbuf,1);//如果对方进程关闭 第一次发送 对方会发送一个 RST(TCP段) 过来	
		write(sock,sendbuf+1,strlen(sendbuf)-1);//第二次发送 对方会发送一个SIGPIPE(信号)过来
		
		
		int ret = readline(sock,recvbuf, 1024 );

		if(ret == -1 ){//当 读数据失败的时候
			exit(1);
		}
		if(ret == 0){//当客户端退出时  read 函数返回 0
			printf("client close\n");
			break;//跳出循环，使这个大函数返回 0  既而时这个 子进程结束
		}

		fputs(recvbuf,stdout);						//6.向终端打印
		
		memset(sendbuf,0,sizeof(sendbuf));
		memset(recvbuf,0,sizeof(recvbuf));		
	}
	close(sock);	
}
void handle_sigpipe(int sig)//作用：捕捉SIGPIPE
{
	printf("recv a sig = %d\n",sig);
}
int main()
{
	signal(SIGPIPE,handle_sigpipe);
	
	int sock;
	int i;
	if((sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("error");
		return 0;	
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5000);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.144");
	
	if(connect(sock,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
		printf("error");
		return 0;	
		
}

	echo_cli(sock);//只选择一个客户端与 服务器通信
	return 0;
}