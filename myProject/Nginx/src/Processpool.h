#ifndef PROCESSPOOL_H
#define PROCESSPOOL_H
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <errno.h> 
#include <sys/socket.h>
#include <assert.h>
#include <signal.h>
#include <netinet/tcp.h> 
#include "easyloggingpp/easylogging++.h"
#include "DtbtNginx.h"
#include "Nginx.h"
using namespace std;

/*描述一个子进程的类*/
class process
{
public:
    process() : m_pid( -1 ){}
public:
    pid_t m_pid;//子进程的PID
    int m_pipefd[2];//父进程和子进程通信用的管道
};

class Processpool
{
private:
	 /*保存所有子进程的描述信息*/
    process *subProcess;
	/*进程允许的最大子进程数量*/
    static const int MAX_processNumber = 16;
    /*每个子进程最多能处理的客户数量*/
    static const int USER_PER_PROCESS = 65536;
    /* 主线程监听的事件 ≈ 集群个数  主线程不同于子线程，监听事件少 */
    static const int MAX_MAIN_PROCESS_EVENT = 100;
    /*epoll最多能处理的事件数*/
    static const int MAX_EVENT = 65536;
    /*进程池中的进程总数*/
    int processNumber;
    /*子进程在池中的序号，从0开始*/
	int childIdx;
    /*每个进程都有一个epoll内核事件表，用epoolfd标识*/
    int epollfd;
    /*监听socket*/
    int listenfd;
    /* 是否主进程来accept */
    bool isFatherAccept;//false 那么当前进程需要继续往下执行，创建新的进程来担当父进程
    /*子进程通过stop来决定是否停止运行*/
    int stop;
    /* 信号管道 */
    static int sigPipefd[2];
protected:
	/*发生信号时的动作*/
	static void sig_handler( int sig );
	/*注册信号*/
	void addsig( int sig, void( handler )(int), bool restart = true );
	/*在epoll事件表中加入fd*/
	void addfd( int epollfd, int fd );
	/*安装信号 创建epoll事件监听表和信号管道*/
	void InitSigPipe();
	/*运行父进程*/
	template< class T >
    void runParent();
	/*运行子进程*/
	template< class T >
    void runChild();
	/*设置非阻塞*/
	int SetNoBlocking(int fd);
	/*epoll内核事件表中删除fd上的所有注册事件*/
	void removefd( int epollfd, int fd );
public:
	/*根据监听套接字创建进程池 默认有4个子进程*/
	Processpool(string ip, int port, int processNumber);
	~Processpool();
	static Processpool *CreateProcesspool( string ip, int port, int processNumber, bool isFatherAccept );
	int CreateListen(string ip, int port);
	/*运行一个父进程或一个子进程*/
	template<class T>
	void run();
};
int Processpool::sigPipefd[2] = {0};

Processpool *Processpool::CreateProcesspool( string ip, int port, int processNumber, bool isFatherAccept){
	if(isFatherAccept){
		return new Processpool(ip, port, processNumber);
	}
	pid_t pid = fork();
	if(0 == pid){
		return NULL;//如果当前进程不是父进程，那么返回空
	}
	else if(pid > 0){
		return new Processpool(ip, port, processNumber);
	}
	else{
		LOG(ERROR) << "CreateProcesspool fork Error";
	}
}
int Processpool::CreateListen(string ip, int port) {
	int ret = 0;
	int listenfd = socket(PF_INET, SOCK_STREAM, 0);
		assert( listenfd >= 0 );
		/*一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。*/
    int reuse = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        return -1;
    }
    struct sockaddr_in address;
    bzero( &address, sizeof(address) );
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    address.sin_port = htons( port );
    
    ret = bind(listenfd, (struct sockaddr*)&address, sizeof( address ));
    if(-1 == ret){
    	LOG(ERROR) << "bind " << ip << " " << port;
    	exit(0);
    }
    
    ret = listen( listenfd, 5 );
    if(-1 == ret){
    	LOG(ERROR) << "listen " << ip << " " << port;
    	exit(0);
    }
    return listenfd;
}
Processpool::Processpool(string ip, int port, int processNumber):processNumber(processNumber) {
	if(processNumber < 0 || processNumber > MAX_processNumber) {
		LOG(ERROR) << "Processpool ";
		return;
	}
	/*初始化监听套接字 最大子进程数量 父进程编号 子进程是否停止运行*/
	listenfd = CreateListen(ip, port);
	processNumber = processNumber;
	childIdx = -1;//进来是父进程 -1
	stop = false;
	
	/*创建用于保存所有子进程的描述信息的指针*/
	subProcess = new process[processNumber];
	assert( subProcess );
	
	/*创建processNumber个子进程，并建立他们和父进程之间的通信管道*/
	for(int idx = 0; idx < processNumber ; idx++) {
		/*还没创建子进程之前 父进程和预定的每一个子进程都先建立一个管道，到时候可以分开通知某一个子进程*/
		int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, subProcess[idx].m_pipefd);
		assert( ret == 0 );
		
		subProcess[idx].m_pid = fork();//创建子进程，并保存子进程id
		assert( subProcess[idx].m_pid >= 0 );
		 
		if( subProcess[idx].m_pid > 0 ) {
            close( subProcess[idx].m_pipefd[1] );//父进程用 pipefd[0] 进程通信
			/* 设置通信管道非阻塞 because : epoll ET mode*/
			if(SetNoBlocking(subProcess[idx].m_pipefd[0]) < 0) {
				LOG(WARNING) << "SetNoBlocking 失败 父subProcess["<< idx <<"].m_pipefd[0] = " << subProcess[idx].m_pipefd[0];
			}
            continue;
         }
        else if(subProcess[idx].m_pid == 0) {
            close( subProcess[idx].m_pipefd[0] );//子进程用 pipefd[1] 进程通信
			if(SetNoBlocking(subProcess[idx].m_pipefd[1]) < 0)	{
				LOG(WARNING) << "SetNoBlocking 失败 子subProcess["<< idx <<"].m_pipefd[0] = " << subProcess[idx].m_pipefd[0];
			}
            childIdx = idx;
            break;
         }
		 else {
		 	LOG(WARNING) << "创建子进程失败";
		 }
	}
}

Processpool::~Processpool() {
	delete [] subProcess;
}

int Processpool::SetNoBlocking(int fd) {
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	return fcntl(fd, F_SETFL, new_option);//如果出错，所有命令都返回-1
}

void Processpool::addfd( int epollfd, int fd )
{
	if(SetNoBlocking(fd) < 0) {
		LOG(WARNING) << "SetNoBlocking 失败";
	}
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;//ET模式  边沿触发***********************************
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}

void Processpool::removefd( int epollfd, int fd ) {
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,NULL);
	close(fd);
}

void Processpool::sig_handler( int sig ) {
    send( sigPipefd[1], ( char * )&sig, 1, 0 );				//向sigPipefd[1]发送一个字节的信号
}

void Processpool::addsig( int sig, void( handler )(int), bool restart) {
	struct sigaction sa;
	memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;									//信号发生时执行的函数
	if( restart ) {
        sa.sa_flags |= SA_RESTART;								//SA_RESTART: 由此信号中断的系统调用会自动重启
    }
    sigfillset( &sa.sa_mask );									//所有的信号加入到此信号集里
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

void Processpool::InitSigPipe() {
	/* 不是父子间通信了，而是系统和进程间的通信*/
    int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, sigPipefd );//初始化信号通道
    assert( ret != -1 );
	
	//信号发生时我们向sigPipefd[1]中发送信息
    if(SetNoBlocking( sigPipefd[1] ) < 0) {
		LOG(WARNING) << "SetNoBlocking 失败";
	}
	addfd( epollfd, sigPipefd[0] );//我们监听sigPipefd[0],当发生触发事件后,可以检测是不是别的进程在给我发信号
	
	/* 设置信号处理函数 */
    addsig( SIGCHLD, sig_handler );//子进程结束信号 
    addsig( SIGTERM, sig_handler );//终止信号 
    addsig( SIGINT, sig_handler );//键盘中断
    addsig( SIGPIPE, SIG_IGN );//SIGPIPE管道破裂（写一个没有读端口的管道 ）SIG_IGN：忽略SIGPIPE信号
}

/*create_pool之后（父子进程都已创建） 接着父子就会调用这个run*/
template< class T >
void Processpool::run() {
    if( childIdx != -1 ) {
        runChild< T >();
        return;
    }
    runParent<T>();
}
/* 子进程需要先解析数，看给哪个服务器集群，然后根据一致性hash选择其中一台服务器 */
template< class T >
void Processpool::runChild() {
	/* 创建epoll事件监听表 */
	epollfd = epoll_create(MAX_EVENT);
	if(-1 == epollfd){
		LOG(ERROR) << "runParent epoll_create";
		return;
	}
	//每个进程都需要注册信号  把信号管道加入到epoll中
	InitSigPipe();
	//每个子进程都通过其在进程池中的序号值childIdx找到与父进程通信的管道
    int pipefd = subProcess[childIdx].m_pipefd[ 1 ];
	//子进程需要监听管道文件描述pipefd，因为父进程将通过它来通知子进程accept新连接
    addfd( epollfd, pipefd );
	
	epoll_event events[ MAX_EVENT ];
    T *users = new T [ USER_PER_PROCESS ];
	assert( users );
    int number = 0;
    int ret = -1;
	int client = 0;
	int sockfd, connfd;
	struct sockaddr_in client_addr;
	socklen_t client_addrlen = sizeof(client_addr);

	while( ! stop )
	{
		number = epoll_wait( epollfd, events, MAX_EVENT, -1);
		if ( ( number < 0 ) && ( errno != EINTR ) )//EINTR由于信号中断，产生的 我们一般会重新执行该系统调用
        {
            printf( "epoll failure\n" );
            break;
        }
		for( int i = 0; i < number ; i++)
		{
			 sockfd = events[i].data.fd;
			 /*接收父进程发过来的信息*/
			 if( ( sockfd == pipefd ) && ( events[i].events & EPOLLIN ) )
			 {
                //从父-子进程之间的管道读取数据，并将结果保存在变量client中。
                //如果读取成功，则表示有新的客户连接到来。
                ret = recv( sockfd, ( char * )&client, sizeof( client ), 0 );
				if(ret == 0)
				{
                    continue;
				}
                if( ( ( ret < 0 ) && ( errno != EAGAIN ) ) )//中断或者没有接收到任何数据
                {
					continue;
                }
				else
				{
					while((connfd = accept( listenfd, (struct sockaddr*)&client_addr, &client_addrlen)) > 0)
					{
						if ( connfd < 0 )                           
						{
							printf( "accept errno is: %d\n", errno );
							continue;
						}
						addfd( epollfd, connfd );
					}
					if (connfd == -1) 
					{
						if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
						perror("accept");
					}
					//模板T必须实现init方法，以初始化一个客户连接
                    //我们直接使用connfd来索引逻辑处理对象
                    //T类型的对象，以提高程序效率
                  //  users[connfd].init( epollfd, connfd, client_address );
				}
			 }
			/*子进程接收到的信号*/
			else if( ( sockfd == sigPipefd[0] ) && ( events[i].events & EPOLLIN ) )
			{
				char signals[1024];
				ret = recv( sigPipefd[0], signals, sizeof( signals ), 0 );
				if( ret <= 0 )
				{
					continue;
				}
				else 
				{
					for( int i = 0; i < ret ; i++)
					{
						switch( signals[i] )
						{
							case SIGCHLD://可以不要
							{
								pid_t pid;
								int stat;
								while ( ( pid = waitpid( -1, &stat, WNOHANG ) ) > 0 )//waitpid()会暂时停止目前进程的执行，直到有信号来到或子进程结束
								{
									printf("waitpid error\n");
									continue;
								}
								wait(NULL);
								break;
							}
							case SIGTERM:
							case SIGINT:
							{
								stop = true;
								break;
							}
							default: break;
						}
					}
				}
			}
			/*客服端请求来到*/
			else if( events[i].events & EPOLLIN ) {
				users[sockfd].Read();
			}
		}
	}
	delete [] users;
    close( pipefd );
    //close( listenfd );
    //来关闭这个文件描述符，即所谓的“对象（比如一个文件描述符，又或者一堆内存）由哪个函数创建，就应该由那个函数销毁
    close( epollfd );
}

/* 
主进程要干的事情：
1.监听一个新的端口，用于DibtNginx通信
2.连接集群中的Nginx
3.给子进程发送 accept 消息
4.给子进程发送 数据同步 消息
*/
template<class T>
void Processpool::runParent() {
	/* 创建epoll事件监听表 */
	epollfd = epoll_create(MAX_MAIN_PROCESS_EVENT);
	if(-1 == epollfd){
		LOG(ERROR) << "runParent epoll_create";
		return;
	}
	/* 创建信号pipe */
	InitSigPipe();

	/* 事件处理Nginx fd既为角标 相当于hash表 减少了查找的时间*/
	Nginx *nginxs = new Nginx[MAX_MAIN_PROCESS_EVENT + 1];
	for(int i = 0; i < MAX_MAIN_PROCESS_EVENT + 1; ++i){
		nginxs[i].epollfd = epollfd;
	}
	//监听 listenfd 
    nginxs[listenfd].sockfd = listenfd;
    nginxs[listenfd].Addfd2Read();

    /* 添加时间处理Nginxs的起始地址 */
	DtbtNginx *dbNginx = Singleton<DtbtNginx>::getInstence();
	dbNginx->nginxs = nginxs;

	/* 创建Dtbt专属的 listenfd */
	int idx = dbNginx->lisName.find(' ');
	string ip(dbNginx->lisName, 0, idx);
	string portStr(dbNginx->lisName, idx + 1, dbNginx->lisName.size());
	int port = atoi(portStr.c_str());
	int dtbtfd = CreateListen(ip, port);
	nginxs[listenfd].sockfd = dtbtfd;
    nginxs[listenfd].Addfd2Read();

	/* 和集群中的其他节点进行连接 */
	dbNginx->ConOtherNginx();
	vector<int> &v = dbNginx->aliveNginxfd;
	int aliveNginxNum = v.size();
	//把成功连接的socket加入epoll   nginx 0 - aliveNginxNum 都是集群中的节点
	for(int i = 0; i < aliveNginxNum; ++i){
		nginxs[v[i]].sockfd = v[i];
		nginxs[v[i]].Addfd2Read();
	}

	epoll_event events[ MAX_EVENT ];
    int sub_process_counter = 0;
    int new_conn = 1;
    int number = 0;
    int ret = -1;
	int sockfd, connfd;
	struct sockaddr_in client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	
	/* 创建一个小根堆 用于 keepalive 和 投票倒计时 */
	vector<int> smallHeap;//毫秒
	smallHeap.push_back(2000);//心跳的间隔为2秒
	//投票 raft定义在：150ms-300ms
	srand(time(0));
	int voteTime = 150 + rand() % 150;
	smallHeap.push_back(voteTime);
	make_heap (smallHeap.begin(),smallHeap.end());

	while( ! stop )	{
		number = epoll_wait( epollfd, events, MAX_EVENT, smallHeap.front());
		if ( ( number < 0 ) && ( errno != EINTR ) ) {
        	LOG(ERROR) << "epoll_wait < 0";
        	break;
        }
		/* timeout */
		if(0 == number){
			//如果是 跟随者 && 还没有leader 那么需要投票
			if(dbNginx->status != LEADER && dbNginx->leaderName[ENSURE].empty()){
				dbNginx->status = CANDIDATE;
				dbNginx->VoteSend();
				/* 如果有了主，那么就不进行选主倒计时了，等keepAlive超时再启动 
				pop_heap(smallHeap.begin(), smallHeap.end()); 
				smallHeap.pop_back(); */
			}
			continue;
		}

		/* 父进程只需要保证 DtbtNginx心跳就行了 */
		dbNginx->SendKeepAlive();

		/* deal events */
		for(int i = 0; i < number; i++)	{
			sockfd = events[i].data.fd;
			/* 新的客服端到来 */
			if(sockfd == listenfd) {
				 //用RR方式将其分配给一个子进程处理
                int i =  sub_process_counter;
                do {
                    if( subProcess[i].m_pid != -1 )	//按进程号次序调用
                    {
                        break;
                    }
                    i = (i + 1) % processNumber;
                } while( i != sub_process_counter );

				/* 如果子进程全部退出，父进程也退出 */
                if( subProcess[i].m_pid == -1 )
                {
                    stop = true;
                    break;
                }
                sub_process_counter = (i + 1) % processNumber;

				/* 随便给子进程发送一个消息，到时候子进程根据是否接受到数据，做出不同的动作 */
                send( subProcess[i].m_pipefd[0], ( char * )&new_conn, sizeof( new_conn ), 0 );
                LOG(DEBUG) << "send request to child " << i;
			}
			/* 父进程接收到的信号 */
			else if( ( sockfd == sigPipefd[0] ) && ( events[i].events & EPOLLIN ) ) {
				char signals[1024];
				ret = recv(sigPipefd[0], signals, sizeof( signals ),0 );
				if( ret <= 0 ) {
					continue;
				}
				else {
					for( int i = 0; i < ret; ++i ) {
						//如果进程池中第i个子进程退出了，
						//则主进程关闭通信管道，并设置相应的m_pid为-1，以标记该子进程已退出
						switch( signals[i] ) {
							case SIGCHLD:
							{
								pid_t pid = -1;
								int stat;
								while( ( pid = waitpid( -1, &stat, WNOHANG) ) > 0 )	{
									/*找到是哪个子进程关闭了 并关闭父子之间的通信管道 并把pid设置-1*/
									for( int i = 0; i < processNumber; ++i ) {
										if( subProcess[i].m_pid == pid ) {
											LOG(INFO) << "child close " << i;
											close( subProcess[i].m_pipefd[0] );
											subProcess[i].m_pid = -1;
										}
									}
								}
								/*如果所有子进程都已经退出了，则父进程也退出*/
								stop = true;
								for( int i = 0; i < processNumber; ++i ) {
									if( subProcess[i].m_pid != -1 )	{
										stop = false;//只要有一个子进程还存在，那么父进程就继续跑
									}
								}
								break;
							}
							case SIGTERM:
							case SIGINT:
							{
								//如果父进程接收到终止信号，那么就杀死所有子进程，并等待它们全部结束，当然，
								//通知子进程结束更好的方法是向父/子进程之间的通信管道发送特殊数据
								LOG(INFO) << "kill all the clild now";
								for( int i = 0; i < processNumber; ++i ) {
									int pid = subProcess[i].m_pid;
									if( pid != -1 )	{
										//kill( pid, SIGTERM );
										kill( pid , SIGKILL );
									}
								}
								break;
							}
							default:break;
						}
					}
				}
			}
			/* 集群 connect */
			else if(sockfd == dtbtfd){
				while((connfd = accept( listenfd, (struct sockaddr*)&client_addr, &client_addrlen)) > 0) {
					if ( connfd < 0 ) {
						LOG(INFO) << "accept errno = " << errno;
						continue;
					}
					//除了启动的时候加入对方fd  连接的时候也要加
					dbNginx->aliveNginxfd.push_back(connfd);
					nginxs[connfd].sockfd = connfd;
					nginxs[connfd].Addfd2Read();
					LOG(DEBUG) << "accept :" << connfd;
				}
			}
			/* 集群消息 */
			else{
				nginxs[sockfd].Read();
			}
		}
	}
    close( listenfd );
    close( epollfd );
}
#endif
/*
int sigfillset(sigset_t * set);
sigfillset()用来将参数set信号集初始化，然后把所有的信号加入到此信号集里即将所有的信号标志位置为1
成功时则返回0；如果有错误则返回-1，并设置errno的值，如果errno的值为EFAULT，则表示参数set指针地址无法存取。

int socketpair(int d, int type, int protocol, int sv[2]);
可以用于网络通信，也可以用于本机内的进程通信
四个参数:		套接口的域　　套接口类型　　使用的协议　　指向存储文件描述符的指针
对于socketpair函数，protocol参数必须提供为0
RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
	   
signal(SIGCHLD, SIG_IGN); 
忽略SIGCHLD信号，这常用于并发服务器的性能的一个技巧
因为并发服务器常常fork很多子进程，子进程终结之后需要服务器进程去wait清理资源。
如果将此信号的处理方式设为忽略，可让内核把僵尸子进程转交给init进程去处理，省去了大量僵尸进程占用系统资源。

*/
/*
1.SIGINT SIGTERM 区别
前者与字符ctrl+c关联，后者没有任何控制字符关联。
前者只能结束前台进程，后者则不是。
2.SIGTERM SIGKILL的区别
前者可以被阻塞、处理和忽略，但是后者不可以。KILL命令的默认不带参数发送的信号就是SIGTERM.让程序有好的退出。
因为它可以被阻塞，所以有的进程不能被结束时，用kill发送后者信号，即可。即：kill -9 进程号。

调度方法
1，SCHED_OTHER 分时调度策略，
2，SCHED_FIFO实时调度策略，先到先服务
3，SCHED_RR实时调度策略，时间片轮转


总结:
这个错误表示资源暂时不够，能read时，读缓冲区没有数据，或者write时，写缓冲区满了。
遇到这种情况，如果是阻塞socket，read/write就要阻塞掉。而如果是非阻塞socket，read/write立即返回-1， 同时errno设置为EAGAIN。
所以，对于阻塞socket，read/write返回-1代表网络出错了。但对于非阻塞socket，read/write返回-1不一定网络真的出错了。
可能是Resource temporarily unavailable。这时你应该再试，直到Resource available。
*/
