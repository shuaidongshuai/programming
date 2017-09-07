//TCP是流协议，并不能保证对方一次性接收确定长度
//也就是说不能保证read一次接收到的就是 对方发送的长度（尽管read函数  第三个参数里面填的是接收1024字节）
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
	char *bufp = buf;
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

int echo_ser(int conn)
{
	char recvbuf[1024];
	while(1)
	{
		memset(recvbuf,0,sizeof(recvbuf));
		int ret = readline(conn,recvbuf,1024 );
		
		if(ret == -1 ){//当 读数据失败的时候
			exit(1);
		}
		if(ret == 0){//当客户端退出时  read 函数返回 0
			printf("client close\n");
			break;//跳出循环，使这个大函数返回 0  既而时这个 子进程结束
		}

		fputs(recvbuf,stdout);
		writen(conn,recvbuf, strlen(recvbuf));
	}
	return 0;
}
/*
pid_t wait(int *status)
进程一旦调用了wait，就立即阻塞自己，由wait自动分析是否当前进程的某个子进程已经退出，如果让它找到了这样一个已经变成僵尸的子进程，
wait就会收集这个子进程的信息，并把它彻底销毁后返回；如果没有找到这样一个子进程，wait就会一直阻塞在这里，直到有一个出现为止。
参数status用来保存被收集进程退出时的一些状态，如果我们对这个子进程是如何死掉的毫不在意，只想把这个僵尸进程消灭掉，我们就可以设定这个参数为NULL
如果成功，wait会返回被收集的子进程的进程ID，如果调用进程没有子进程，调用就会失败，此时wait返回-1，同时errno被置为ECHILD
*/
/*
waitpid()会暂时停止目前进程的执行，直到有信号来到或子进程结束。
*/
//自己试验和视频上的不一样，可能内核升级了吧，不用循环  有时候也会全部杀死僵死进程(有时候不会)(按理来说每个wait或waitpid只能处理一个子进程啊),,但是用了循环之后就再也看不到僵死进程了
void dong_sigchld(int sig)
{
	//pid_t pid = wait(NULL);
	pid_t   pid;
   while((pid = waitpid(-1, NULL, WNOHANG)) > 0){
		   printf("child %d terminated\n", pid);
   }
}

int main()
{
	//避免僵死进程	SIGCHLD，在一个进程终止或者停止时，将SIGCHLD信号发送给其父进程，按系统默认将忽略此信号，如果父进程希望被告知其子系统的这种状态，则应捕捉此信号
	//第一种方法  
	/* signal(SIGCHLD,SIG_IGN);*/
	//第二种方法		
	signal(SIGCHLD,dong_sigchld);
	
	int listenfd;
	if((listenfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("error");
		return 0;
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1024);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.144");
	
/*	int on = 1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))){	
		return 0;
	}																	*/					
	
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
			  echo_ser(conn);
			  return 0;   //客服端关闭了 子进程就没有存在的必要了
		  }
		  else
			  close(conn);//父进程  关闭已连接套接字，就可以监听其他客服端的请求了
	  }	  	
	return 0;
}
