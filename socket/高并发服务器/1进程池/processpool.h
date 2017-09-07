#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>

//描述一个子进程的类，
//m_pid是目标子进程的PID，m_pipefd是父进程和子进程通信用的管道
class process
{
public:
    process() : m_pid( -1 ){}

public:
    pid_t m_pid;
    int m_pipefd[2];
};

//将它定义为模板类是为了代码复用
//其模板参数是处理逻辑任务的类
template< typename T >
class processpool
{
private:
    //将构造函数定义为私有，因此我们只能通过后面的create静态函数来创建
    //processpool实例
    processpool( int listenfd, int process_number = 8 );
public:
    //单例模式，以保证程序最多创建一个processpool实例，这是程序正确处理信号的必要条件
    static processpool< T > *create( int listenfd, int process_number = 8 )
    {
        if( !m_instance )
        {
            m_instance = new processpool< T >( listenfd, process_number );
        }
        return m_instance;
    }
    ~processpool()
    {
        delete [] m_sub_process;
    }
    //启动进程池
    void run();

private:
    void setup_sig_pipe();
    void run_parent();
    void run_child();

private:
    //进程允许的最大子进程数量
    static const int MAX_PROCESS_NUMBER = 16;
    //每个子进程最多能处理的客户数量
    static const int USER_PER_PROCESS = 65536;
    //epoll最多能处理的事件数
    static const int MAX_EVENT_NUMBER = 10000;
    //进程池中的进程总数
    int m_process_number;
    //子进程在池中的序号，从0开始
    int m_idx;
    //每个进程都有一个epoll内核事件表，用m_epoolfd标识
    int m_epollfd;
    //监听socket
    int m_listenfd;
    //子进程通过m_stop来决定是否停止运行
    int m_stop;
    //保存所有子进程的描述信息
    process *m_sub_process;
    //进程池静态实例
    static processpool< T > *m_instance;
};

template< typename T >
processpool< T > *processpool< T >::m_instance = NULL;

//用于处理信号的管道，以实现统一事件源，后面称之为信号管道
static int sig_pipefd[2];

static int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

static void addfd( int epollfd, int fd )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}
//从epollfd标识的epoll内核事件表中删除fd上的所有注册事件
static void removefd( int epollfd, int fd )
{
    epoll_ctl( epollfd, EPOLL_CTL_DEL, fd, 0 );
    close( fd );
}

static void sig_handler( int sig )
{
    int save_errno = errno;
    int msg = sig;
    send( sig_pipefd[1], ( char * )&msg, 1, 0 );
    errno = save_errno;
}

//注册信号
static void addsig( int sig, void( handler )(int), bool restart = true )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;
    if( restart )
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset( &sa.sa_mask );									//将所有的信号标志位置为1，
    assert( sigaction( sig, &sa, NULL ) != -1 );
}
//进程池构造函数。
//参数listenfd是监听socket，它必须在创建进程池之前被创建，否则
//子进程无法直接引用它，参数process_number指定进程池中子进程的数量。
template< typename T >
processpool< T >::processpool( int listenfd, int process_number )
    : m_listenfd( listenfd ), m_process_number( process_number ), m_idx( -1 ), m_stop( false )
{
    assert( ( process_number > 0 ) && ( process_number <= MAX_PROCESS_NUMBER ) );

    m_sub_process = new process[ process_number ];
    assert( m_sub_process );
    //创建process_number个子进程，并建立他们和父进程之间的管道
    for( int i = 0; i < process_number; ++i )
    {
        int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, m_sub_process[i].m_pipefd );
        assert( ret == 0 );

        m_sub_process[i].m_pid = fork();
        assert( m_sub_process[i].m_pid >= 0 );
        if( m_sub_process[i].m_pid > 0 )
        {
            close( m_sub_process[i].m_pipefd[1] );//父进程用 pipefd[0]
            continue;
        }
        else
        {
            close( m_sub_process[i].m_pipefd[0] );//子进程用 pipefd[1]
            m_idx = i;
            break;
        }
    }
}
//统一事件源
template< typename T >
void processpool< T >::setup_sig_pipe()
{
    //创建epoll事件监听表和信号管道
    m_epollfd = epoll_create( 5 );
    assert( m_epollfd != -1 );

    int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, sig_pipefd );
    assert( ret != -1 );

    setnonblocking( sig_pipefd[1] );
    addfd( m_epollfd, sig_pipefd[0] );
    //设置信号处理函数
    addsig( SIGCHLD, sig_handler );//子进程结束信号 
    addsig( SIGTERM, sig_handler );//终止信号 
    addsig( SIGINT, sig_handler );//键盘中断
    addsig( SIGPIPE, SIG_IGN );//SIGPIPE管道破裂: 写一个没有读端口的管道 
}
//父进程中m_idx值为-1，子进程中m_idx值大于等于0，我们据此判断下来
//要运行的是父进程代码还是子进程代码
template< typename T >
void processpool< T >::run()
{
    if( m_idx != -1 )
    {
        run_child();
        return;
    }
    run_parent();
}

template< typename T >
void processpool< T >::run_child()
{
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

    while( ! m_stop )
    {
        number = epoll_wait( m_epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ( number < 0 ) && ( errno != EINTR ) )//EINTR由于信号中断，产生的
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            if( ( sockfd == pipefd ) && ( events[i].events & EPOLLIN ) )
            {
                int client = 0;
                //从父/子进程之间的管道读取数据，并将结果保存在变量client中。
                //如果读取成功，则表示有新的客户连接到来。
                ret = recv( sockfd, ( char * )&client, sizeof( client ), 0 );
                if( ( ( ret < 0 ) && ( errno != EAGAIN ) ) || ret == 0 )
                {
                    continue;
                }
                else
                {
                    struct sockaddr_in client_address;
                    socklen_t client_addrlength = sizeof( client_address );
                    int connfd = accept( m_listenfd, ( struct sockaddr * )&client_address, &client_addrlength );
                    if ( connfd < 0 )
                    {
                        printf( "errno is: %d\n", errno );
                        continue;
                    }
                    addfd( m_epollfd, connfd );
                    //模板T必须实现init方法，以初始化一个客户连接
                    //我们直接使用connfd来索引逻辑处理对象
                    //T类型的对象，以提高程序效率
                    users[connfd].init( m_epollfd, connfd, client_address );
                }
            }
            //下面处理子进程接收到的信号
            else if( ( sockfd == sig_pipefd[0] ) && ( events[i].events & EPOLLIN ) )
            {
                int sig;
                char signals[1024];
                ret = recv( sig_pipefd[0], signals, sizeof( signals ), 0 );
                if( ret <= 0 )
                {
                    continue;
                }
                else
                {
                    for( int i = 0; i < ret; ++i )
                    {
                        switch( signals[i] )
                        {
                        case SIGCHLD:
                        {
                            pid_t pid;
                            int stat;
                            while ( ( pid = waitpid( -1, &stat, WNOHANG ) ) > 0 )
                            {
                                continue;
                            }
                            break;
                        }
                        case SIGTERM:
                        case SIGINT:
                        {
                            m_stop = true;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                        }
                    }
                }
            }
            //如果是其他可读数据，那么必然是客户请求到来。
            //调用逻辑对象的process方法处理之
            else if( events[i].events & EPOLLIN )
            {
                users[sockfd].process();
            }
            else
            {
                continue;
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

template< typename T >
void processpool< T >::run_parent()
{
    setup_sig_pipe();
    //父进程监听m_listenfd
    addfd( m_epollfd, m_listenfd );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int sub_process_counter = 0;
    int new_conn = 1;
    int number = 0;
    int ret = -1;

    while( ! m_stop )
    {
        number = epoll_wait( m_epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            if( sockfd == m_listenfd )
            {
                //如果有新连接到来，就采用RR方式将其分配给一个子进程处理
                int i =  sub_process_counter;
                do
                {
                    if( m_sub_process[i].m_pid != -1 )
                    {
                        break;
                    }
                    i = (i + 1) % m_process_number;
                }
                while( i != sub_process_counter );

                if( m_sub_process[i].m_pid == -1 )
                {
                    m_stop = true;
                    break;
                }
                sub_process_counter = (i + 1) % m_process_number;
                //send( m_sub_process[sub_process_counter++].m_pipefd[0], ( char* )&new_conn, sizeof( new_conn ), 0 );
                send( m_sub_process[i].m_pipefd[0], ( char * )&new_conn, sizeof( new_conn ), 0 );
                printf( "send request to child %d\n", i );
                //sub_process_counter %= m_process_number;
            }
            //下面处理父进程接收到的信号
            else if( ( sockfd == sig_pipefd[0] ) && ( events[i].events & EPOLLIN ) )
            {
                int sig;
                char signals[1024];
                ret = recv( sig_pipefd[0], signals, sizeof( signals ), 0 );
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
                            pid_t pid;
                            int stat;
                            while ( ( pid = waitpid( -1, &stat, WNOHANG ) ) > 0 )
                            {
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
                            //如果所有子进程都已经退出了，则父进程也退出
                            m_stop = true;
                            for( int i = 0; i < m_process_number; ++i )
                            {
                                if( m_sub_process[i].m_pid != -1 )
                                {
                                    m_stop = false;
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
                                    kill( pid, SIGTERM );
                                }
                            }
                            break;
                        }
                        default:
                        {
                            break;
                        }
                        }
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }
    //由创建者关闭这个文件描述符
    //close( m_listenfd );
    close( m_epollfd );
}
/*
int sigfillset(sigset_t * set);
sigfillset()用来将参数set信号集初始化，然后把所有的信号加入到此信号集里即将所有的信号标志位置为1，
屏蔽所有的信号。它是一个宏实现，如下所示：
#define sigfillset(ptr) ( *(ptr) = ~(sigset_t)0, 0)
因为函数sigfillset必须返回0，所以使用C语言里面的逗号运算符，它将逗号运算符后的值做为表达式的值返回。
函数在执行成功时则返回0；如果有错误则返回-1，并设置errno的值，如果errno的值为EFAULT，则表示参数set指针地址无法存取。

int socketpair(int domain, int type, int protocol, int sv[2]);
　	套接口的域
　　套接口类型
　　使用的协议						于socketpair函数，protocol参数必须提供为0。
　　指向存储文件描述符的指针
参数sv[2]是接收代表两个套接口的整数数组。每一个文件描述符代表一个套接口，并且与另一个并没有区别。
　　如果函数成功，将会返回0值。否则将会返回-1表明创建失败，并且errno来表明特定的错误号。
　　关于流程。socketpair()函数创建出两个进程，fork()之后这两个进程都会执行主程序中的代码，这个一定要注意！尤其是bind的时候，
	如果bind两次的话，那就会出错了。一般会在子进程里调用一个带死循环的函数，这样就好了。

	
signal(SIGCHLD, SIG_IGN); //忽略SIGCHLD信号，这常用于并发服务器的性能的一个技巧
//因为并发服务器常常fork很多子进程，子进程终结之后需要
//服务器进程去wait清理资源。如果将此信号的处理方式设为
//忽略，可让内核把僵尸子进程转交给init进程去处理，省去了
//大量僵尸进程占用系统资源。(Linux Only)


pid_t waitpid(pid_t pid,int * status,int options);会暂时停止目前进程的执行，直到有信号来到或子进程结束。
如果不在意结束状态值,则参数 status 可以设成 NULL。参数 pid 为欲等待的子进程识别码,
pid<-1 等待进程组识别码为 pid 绝对值的任何子进程。
pid=-1 等待任何子进程,相当于 wait()。
pid=0 等待进程组识别码与目前进程相同的任何子进程。
pid>0 等待任何子进程识别码为 pid 的子进程。
参数options提供了一些额外的选项来控制waitpid，参数 option 可以为 0 或可以用"|"运算符把它们连接起来使用，比如：
ret=waitpid(-1,NULL,WNOHANG | WUNTRACED);
如果我们不想使用它们，也可以把options设为0
WNOHANG 若pid指定的子进程没有结束，则waitpid()函数返回0，不予以等待。若结束，则返回该子进程的ID。


1，RR调度和FIFO调度的进程属于实时进程，以分时调度的进程是非实时进程。
2，当实时进程准备就绪后，如果当前cpu正在运行非实时进程，则实时进程立即抢占非实时进程。
3，RR进程和FIFO进程都采用实时优先级做为调度的权值标准，RR是FIFO的一个延伸。FIFO时，如果两个进程的优先级一样
	则这两个优先级一样的进程具体执行哪一个是由其在队列中的未知决定的，这样导致一些不公正性(优先级是一样的，
	为什么要让你一直运行？)，如果将两个优先级一样的任务的调度策略都设为RR，则保证了这两个任务可以循环执行，保证了公平。
*/