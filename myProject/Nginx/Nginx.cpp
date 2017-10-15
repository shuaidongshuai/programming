#include "nginx.h"
#include "Processpool.h"

using namespace std;

int serverfd[MAX_SERVER_NUM] = {-1};//保存服务器ip
int Nginx::checkserverfd[5] = {-1};
map<int, int> keep_session;

void Nginx::process(int sockfd)
{
	int serverNum = -1;
	char buf[1024];
	int nread = 0;
	int nwrite = 0;
	int n;
	while ((n = read(sockfd, buf + nread, 1024)) > 0) 
	{
		nread += n;
	}
	if (nread == -1) 
	{
		perror("客服端异常退出");
		close(sockfd);//-----------------------心跳机制
		return;
	}
	if (nread == 0)
	{
		printf("客服端正常退出\n");
		return;
	}
	

	/* 会话保持 如果用了一致性Hash，会话保持就不应该出现在这，应该在通知子进程的时候进行会话保持 */
	for(map<int, int>::iterator it = keep_session.begin(); it != keep_session.end(); it++)
	{
		if(it->first == sockfd)
			serverNum = it->second;
	}
	if(serverNum == -1)
	{
		printf("没找到服务器\n");
		return;
	}

	// n = nread;
	// while (n > 0)
	// {
		// nwrite = write(serverfd[i], buf + nread - n, n);//从 data_size - n 处开始读 读n个
		// n -= nwrite;
	// }

	// bzero(buf,sizeof(buf));
	// nread = 0;
	// while ((n = read(serverfd[i], buf + nread, 1024)) > 0) 
	// {
		// nread += n;
	// }
	// if (nread == -1 && errno != EAGAIN) 
	// {
		// perror("read error");
		// return;
	// }
	// if (nread == 0) 
	// {
		// printf("服务器退出 nread = %d  n = %d\n",nread,n);
		// return;
	// }
	
	buf[nread] = 0;
	printf("收到：%s",buf);
	
	write(serverfd[serverNum], buf, nread);
	bzero(buf,sizeof(buf));
	nread = read(serverfd[serverNum], buf, 1024);
	//recv() 返回 -1，且 errno 不等于 EAGAIN，表示 recv 操作遇到系统错误 errno。
	if (nread == -1 && errno != EAGAIN) 
	{
		perror("read error");
		close(serverfd[serverNum]);//-----------------------心跳机制
		checkserverfd[serverNum] = -1;
		return ;
	}
	
	n = nread;
	while (n > 0)
	{
		nwrite = write(sockfd, buf + nread - n, n);//从 data_size - n 处开始读 读n个
		n -= nwrite;
	}
}

void Nginx::setnonblocking(int fd)
{
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
}

void Nginx::connectServer()
{
	struct sockaddr_in servaddr;
	for(int i = 0; i < 5; i++)
	{
		if((serverfd[i] = socket(AF_INET,SOCK_STREAM,0)) < 0)
		{
			printf("创建socket失败\n");
			exit(0);
		}
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		inet_pton(AF_INET,SERVER_IPADDR,&servaddr.sin_addr);
		servaddr.sin_port = htons(BASE_SERVER_PORT + i);
		
		if(connect(serverfd[i],(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
		{
			printf("Server%d\t端口：%d\t连接失败\n",i,BASE_SERVER_PORT + i);
			continue;
		}
		printf("Server%d\t端口：%d\t连接成功\n",i,BASE_SERVER_PORT + i);
		checkserverfd[i] = 1;
		//setnonblocking(serverfd[i]);
	}
}
void Nginx::sendtoServer(int clientfd)
{
}
char* Nginx::receivefromServer()
{
}

int main()
{
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert( listenfd >= 0 );
	
	 /*一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。*/
    int reuse = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        return -1;
    }
    
    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof(address) );
    address.sin_family = AF_INET;
    inet_pton(AF_INET, NGINX_IPADDR, &address.sin_addr);
    address.sin_port = htons( NGINX_PORT );
    
    ret = bind(listenfd, (struct sockaddr*)&address, sizeof( address ));
    assert( ret != -1);
    
    ret = listen( listenfd, 5 );
    assert(ret != -1);
    
	//连接服务器
	Nginx::connectServer();
	
    Processpool* pool = Processpool::createPool( listenfd , 1);
    if( pool )
    {
        pool->run<Nginx>();
        delete pool;
    }
    close(listenfd); /*正如前文提到，main函数创建了文件描述符listenfd，那么就由它亲自关闭*/
	return 0;
}