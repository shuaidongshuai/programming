#include "common.h"
#include "WRR.h"

using namespace std;

int set_tcp_keepAlive(int fd, int start, int interval, int count);

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
	/*采用单例设计模式*/
	static Processpool *pool;
	 /*保存所有子进程的描述信息*/
    process *m_sub_process;
	/*进程允许的最大子进程数量*/
    static const int MAX_PROCESS_NUMBER = 4;
    /*每个子进程最多能处理的客户数量*/
    static const int USER_PER_PROCESS = 65536;
    /*epoll最多能处理的事件数*/
    static const int MAX_EVENT_NUMBER = 65536;
    /*进程池中的进程总数*/
    int m_process_number;
    /*子进程在池中的序号，从0开始*/
	int m_idx;
    /*每个进程都有一个epoll内核事件表，用m_epoolfd标识*/
    int m_epollfd;
    /*监听socket*/
    int m_listenfd;
    /*子进程通过m_stop来决定是否停止运行*/
    int m_stop;
	/*加权轮循算法*/
	static WRR *wrr;
private:
	Processpool( int listenfd, int process_number );
	/*发生信号时的动作*/
	static void sig_handler( int sig );
	/*注册信号*/
	static void addsig( int sig, void( handler )(int), bool restart = true );
	/*在epoll事件表中加入fd*/
	void addfd( int epollfd, int fd );
	/*安装信号 创建epoll事件监听表和信号管道*/
	void setup_sig_pipe();
	/*运行父进程*/
	template< class T >
    void run_parent();
	/*运行子进程*/
	template< class T >
    void run_child();
	/*设置非阻塞*/
	int setnonblocking(int fd);
	/*epoll内核事件表中删除fd上的所有注册事件*/
	void removefd( int epollfd, int fd );
public:
	/*根据监听套接字创建进程池 默认有2个子进程*/
	static Processpool* createPool( int listenfd, int process_number = 2 );
	~Processpool();
	/*运行一个父进程或一个子进程*/
	template<class T>
	void run();
};

static int sig_pipefd[2];
WRR *Processpool::wrr = NULL;
Processpool *Processpool::pool = NULL;
extern map<int, int> keep_session;

Processpool* Processpool::createPool( int listenfd, int process_number )
{
	if( !pool )
	{
		pool = new Processpool( listenfd, process_number );
		wrr = new WRR;
	}
	return pool;
}
int Processpool::setnonblocking(int fd)
{
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	return fcntl(fd,F_SETFL,new_option);//如果出错，所有命令都返回-1
}

Processpool::Processpool( int listenfd, int process_number )
{
	assert( ( process_number > 0 ) && ( process_number <= MAX_PROCESS_NUMBER ) );
	
	/*初始化监听套接字 最大子进程数量 子进程在池中的序号 子进程是否停止运行*/
	m_listenfd = listenfd;
	m_process_number = process_number;
	m_idx = -1;//进来的是父进程，所以设置成 -1
	m_stop = false;
	
	/*创建用于保存所有子进程的描述信息的指针*/
	m_sub_process = new process[ process_number ];
	assert( m_sub_process );
	
	/*创建process_number个子进程，并建立他们和父进程之间的通信管道*/
	for(int i = 0; i < process_number ; i++)
	{
		/*还没创建子进程之前 父进程和预定的每一个子进程都先建立一个管道，到时候可以分开通知某一个子进程*/
		int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, m_sub_process[i].m_pipefd);
		assert( ret == 0 );
		
		 m_sub_process[i].m_pid = fork();//创建子进程，并保存子进程id
		 assert( m_sub_process[i].m_pid >= 0 );
		 
		 if( m_sub_process[i].m_pid > 0 )
         {
             close( m_sub_process[i].m_pipefd[1] );//父进程用 pipefd[0] 进程通信
			/* 设置通信管道非阻塞 because : epoll ET mode*/
			if(setnonblocking(m_sub_process[i].m_pipefd[0]) < 0)
			{
				perror("setnonblocking 失败");
			}
             continue;
         }
         else if(m_sub_process[i].m_pid == 0)
         {
             close( m_sub_process[i].m_pipefd[0] );//子进程用 pipefd[1] 进程通信
			if(setnonblocking(m_sub_process[i].m_pipefd[0]) < 0)
			{
				perror("setnonblocking 失败");
			}
             m_idx = i;
             break;
         }
		 else
		 {
			 perror("创建子进程失败");
		 }
	}
}

Processpool::~Processpool()
{
	delete [] m_sub_process;
}

void Processpool::addfd( int epollfd, int fd )
{
	if(setnonblocking(fd) < 0)
	{
		perror("setnonblocking 失败");
	}
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;//ET模式  边沿触发***********************************
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}
void Processpool::removefd( int epollfd, int fd )
{
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,NULL);
	close(fd);
}

void Processpool::sig_handler( int sig )
{
    send( sig_pipefd[1], ( char * )&sig, 1, 0 );				//向sig_pipefd[1]发送一个字节的信号
}

void Processpool::addsig( int sig, void( handler )(int), bool restart)
{
	struct sigaction sa;
	memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;									//信号发生时执行的函数
	if( restart )
    {
        sa.sa_flags |= SA_RESTART;								//SA_RESTART: 由此信号中断的系统调用会自动重启
    }
    sigfillset( &sa.sa_mask );									//所有的信号加入到此信号集里
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

void Processpool::setup_sig_pipe()
{
	/*创建epoll事件监听表  把信号管道加入到监听表中*/
	m_epollfd = epoll_create(MAX_EVENT_NUMBER);
	assert( m_epollfd != -1 );

	/*这里想了好久，为啥和初始化通信管道的位置不一样？  原因：不是父子间通信了，而是系统和进程间的通信*/
    int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, sig_pipefd );//初始化信号通道
    assert( ret != -1 );
	
    if(setnonblocking( sig_pipefd[1] ) < 0)//信号发生时我们向sig_pipefd[1]中发送信息
	{
		perror("setnonblocking 失败");
	}
	addfd( m_epollfd, sig_pipefd[0] );//我们监听sig_pipefd[0],当发生触发事件后,可以检测是不是别的进程在给我发信号
	
	/*设置信号处理函数*/
    addsig( SIGCHLD, sig_handler );//子进程结束信号 
    addsig( SIGTERM, sig_handler );//终止信号 
    addsig( SIGINT, sig_handler );//键盘中断
    addsig( SIGPIPE, SIG_IGN );//SIGPIPE管道破裂（写一个没有读端口的管道 ）SIG_IGN：忽略SIGPIPE信号
}

/*create_pool之后（父子进程都已创建） 接着父子就会调用这个run*/
template< class T >
void Processpool::run()
{
    if( m_idx != -1 )
    {
        run_child< T >();
        return;
    }
    run_parent<T>();
}

template< class T >
void Processpool::run_child()
{
	//每个进程都需要注册信号  把信号管道加入到epoll中
	setup_sig_pipe();
	//每个子进程都通过其在进程池中的序号值m_idx找到与父进程通信的管道
    int pipefd = m_sub_process[m_idx].m_pipefd[ 1 ];
	//子进程需要监听管道文件描述pipefd，因为父进程将通过它来通知子进程accept新连接
    addfd( m_epollfd, pipefd );
	
	epoll_event events[ MAX_EVENT_NUMBER ];
    T *users = new T [ USER_PER_PROCESS ];
	assert( users );
    int number = 0;
    int ret = -1;
	int client = 0;
	int sockfd, connfd;
	struct sockaddr_in client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	
	while( ! m_stop )
	{
		number = epoll_wait( m_epollfd, events, MAX_EVENT_NUMBER, -1);
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
                //从父/子进程之间的管道读取数据，并将结果保存在变量client中。
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
					while((connfd = accept( m_listenfd, (struct sockaddr*)&client_addr, &client_addrlen)) > 0)
					{
						if ( connfd < 0 )                           
						{
							printf( "errno is: %d\n", errno );
							continue;
						}
						addfd( m_epollfd, connfd );
						set_tcp_keepAlive(connfd,60,30,5);
						
						//用加权轮循的方法，选出一个服务器，并和这个客服端进行绑定（会话保持）
						int num = wrr->get();
						keep_session.insert(map<int, int>::value_type(connfd, num));
						
						cout<<"IP:"<<inet_ntoa(client_addr.sin_addr)<<"  port:"<<ntohs(client_addr.sin_port)<<"  sockfd:"<<connfd<<endl;
					}
					if (connfd == -1) 
					{
						if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
						perror("accept");
					}
					//模板T必须实现init方法，以初始化一个客户连接
                    //我们直接使用connfd来索引逻辑处理对象
                    //T类型的对象，以提高程序效率
                  //  users[connfd].init( m_epollfd, connfd, client_address );
				}
			 }
			/*子进程接收到的信号*/
			else if( ( sockfd == sig_pipefd[0] ) && ( events[i].events & EPOLLIN ) )
			{
				char signals[1024];
				ret = recv( sig_pipefd[0], signals, sizeof( signals ), 0 );
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
								m_stop = true;
								break;
							}
							default: break;
						}
					}
				}
			}
			/*客服端请求来到*/
			else if( events[i].events & EPOLLIN )
			{
				users[sockfd].process(sockfd);
			}
		}
	}
	delete [] users;
    users = NULL;
    close( pipefd );
    //close( m_listenfd );
    //我们将这句话注销掉，以提醒读者，应该有m_listenfd的创建者
    //来关闭这个文件描述符，即所谓的“对象（比如一个文件描述符，又或者一堆内存）由那个函数创建，就应该由那个函数销毁
    close( m_epollfd );
}

template<class T>
void Processpool::run_parent()
{
	setup_sig_pipe();
    //父进程监听m_listenfd
    addfd( m_epollfd, m_listenfd );
	
	epoll_event events[ MAX_EVENT_NUMBER ];
    int sub_process_counter = 0;
    int new_conn = 1;
    int number = 0;
    int ret = -1;
	int sockfd;
	
	while( ! m_stop )
	{
		number = epoll_wait( m_epollfd, events, MAX_EVENT_NUMBER, -1);
		if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }
		
		for(int i = 0; i < number; i++)
		{
			sockfd = events[i].data.fd;
			/*新的客服端到来*/
			if(sockfd == m_listenfd)
			{
				 //用RR方式将其分配给一个子进程处理***************************
                int i =  sub_process_counter;
                do
                {
                    if( m_sub_process[i].m_pid != -1 )	//按进程号次序调用
                    {
                        break;
                    }
                    i = (i + 1) % m_process_number;
                }
                while( i != sub_process_counter );

				/*如果子进程全部退出，父进程也退出*/
                if( m_sub_process[i].m_pid == -1 )
                {
                    m_stop = true;
                    break;
                }
                sub_process_counter = (i + 1) % m_process_number;

				/*随便给子进程发送一个消息，到时候子进程根据是否接受到数据，做出不同的动作*/
                send( m_sub_process[i].m_pipefd[0], ( char * )&new_conn, sizeof( new_conn ), 0 );
                printf( "send request to child %d\n", i );
			}
			/*父进程接收到的信号*/
			else if( ( sockfd == sig_pipefd[0] ) && ( events[i].events & EPOLLIN ) )
			{
				char signals[1024];
				ret = recv(sig_pipefd[0], signals, sizeof( signals ),0 );
				if( ret <= 0 )
				{
					continue;
				}
				else
				{
					for( int i = 0; i < ret; ++i )
					{
						//如果进程池中第i个子进程退出了，
						//则主进程关闭通信管道，并设置相应的m_pid为-1，以标记该子进程已退出
						switch( signals[i] )
						{
							case SIGCHLD:
							{
								pid_t pid = -1;
								int stat;
								while( ( pid = waitpid( -1, &stat, WNOHANG) ) > 0 )
								{
									/*找到是哪个子进程关闭了 并关闭父子之间的通信管道 并把pid设置-1*/
									for( int i = 0; i < m_process_number; ++i )
									{
										if( m_sub_process[i].m_pid == pid )
										{
											printf( "child %d join\n", i );
											close( m_sub_process[i].m_pipefd[0] );
											m_sub_process[i].m_pid = -1;
										}
									}
								}
								/*如果所有子进程都已经退出了，则父进程也退出*/
								m_stop = true;
								for( int i = 0; i < m_process_number; ++i )
								{
									if( m_sub_process[i].m_pid != -1 )
									{
										m_stop = false;//只要有一个子进程还存在，那么父进程就继续跑
									}
								}
								break;
							}
							case SIGTERM:
							case SIGINT:
							{
								//如果父进程接收到终止信号，那么就杀死所有子进程，并等待它们全部结束，当然，
								//通知子进程结束更好的方法是向父/子进程之间的通信管道发送特殊数据
								printf( "kill all the clild now\n" );
								for( int i = 0; i < m_process_number; ++i )
								{
									int pid = m_sub_process[i].m_pid;
									if( pid != -1 )
									{
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
		}
	}
	//由创建者关闭这个文件描述符
    //close( m_listenfd );
    close( m_epollfd );
}
/*
总结：
1.不能同时创建.cpp文件。。编译链接会出错
有模板的类。。和模板类。。和普通类在定义函数的时候很不一样
有模板函数的类和模板类 定义声明要放在.h文件中
如果定义成类的形式：有.cpp 和 .h 文件。。那么普通类函数就不能把定义写在.h文件中  .h文件中只能有声明
如果没有.cpp文件，那么就没这些限制了，因为include的时候就是简单的代码展开

*/
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
