#include<stdio.h>  
#include<string.h>  
#include<errno.h>  
  
#include<unistd.h>  
#include<event.h>  
  
void accept_cb(int fd, short events, void* arg);  
void socket_read_cb(int fd, short events, void *arg);  
int tcp_server_init(int port, int listen_num);  
  
int main(int argc, char** argv)  
{  
    int listener = tcp_server_init(9999, 10);  
    if( listener == -1 )  
    {  
        perror(" tcp_server_init error ");  
        return -1;  
    }  
  
    struct event_base* base = event_base_new();  
  
    //添加监听客户端请求连接事件  
    struct event* ev_listen = event_new(base, listener, EV_READ | EV_PERSIST,  //监听了listener
                                        accept_cb, 
										base);
    event_add(ev_listen, NULL);//激活

    event_base_dispatch(base);//循环监听
  
    return 0;  
}
  
void accept_cb(int fd, short events, void* arg)  
{  
    evutil_socket_t sockfd;  
  
    struct sockaddr_in client;  
    socklen_t len = sizeof(client);  
  
    sockfd = ::accept(fd, (struct sockaddr*)&client, &len );  
    evutil_make_socket_nonblocking(sockfd);  
  
    printf("accept a client %d\n", sockfd);  
  
    struct event_base* base = (event_base*)arg;  
  
    //仅仅是为了动态创建一个event结构体  
    struct event *ev = event_new(NULL, -1, 0, NULL, NULL);  
    //这里还需要监听刚刚连接上的socket
    event_assign(ev, base, sockfd, EV_READ | EV_PERSIST,  
                 socket_read_cb, (void*)ev);  
  
    event_add(ev, NULL);
}  
  
  
void socket_read_cb(int fd, short events, void *arg)  
{  
    char msg[4096];  
    struct event *ev = (struct event*)arg;  
    int len = read(fd, msg, sizeof(msg) - 1);  
    if( len <= 0 )
    {
		if(0 == len)
			printf("client closed\n");
        else
			printf("some error happen when read\n");  
        event_free(ev);  
        close(fd);  
        return ;  
    }
  
    msg[len] = '\0';  
    printf("recv the client msg: %s", msg);  
  
    char reply_msg[4096] = "I have recvieced the msg: ";  
    strcat(reply_msg + strlen(reply_msg), msg);  
  
    write(fd, reply_msg, strlen(reply_msg) );  
}  
  
int tcp_server_init(int port, int listen_num)  
{  
    int errno_save;  
    evutil_socket_t listener;  
  
    listener = ::socket(AF_INET, SOCK_STREAM, 0);  
    if( listener == -1 )  
        return -1;  
  
    //允许多次绑定同一个地址。要用在socket和bind之间  
    evutil_make_listen_socket_reuseable(listener);  
  
    struct sockaddr_in sin;  
    sin.sin_family = AF_INET;  
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);  
  
    if( ::bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0 )  
        goto error;  
  
    if( ::listen(listener, listen_num) < 0)  
        goto error;  
  
  
    //跨平台统一接口，将套接字设置为非阻塞状态  
    evutil_make_socket_nonblocking(listener);  
  
    return listener;  
  
    error: 
        errno_save = errno;  
        evutil_closesocket(listener);  
        errno = errno_save;  
  
        return -1;  
}
/*
int evutil_make_listen_socket_reuseable(evutil_socket_t sock)
{
#ifndef WIN32
	int one = 1;
	return setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*) &one,
	    (ev_socklen_t)sizeof(one));
#else
	return 0;
#endif
}



int event_assign（（struct event * ev，struct event_base * base，evutil_socket_t fd,short event，event_callback_fn fn，void * arg）
函数event_assign（）准备在将来对event_add（）和event_del（）的调用中使用的事件结构ev 。
事件将准备调用由fn参数指定的函数，使用指示文件描述符的int参数，指示事件类型的short参数和arg参数中指定的void *参数。fd表示应监视事件的文件描述符。事件可以是EV_READ，EV_WRITE或两者。指示应用程序可以分别从文件描述符读取或写入而不阻塞。
将使用触发事件的文件描述符和将为EV_TIMEOUT，EV_SIGNAL，EV_READ或EV_WRITE的事件类型调用函数fn。附加标志EV_PERSIST使event_add（）持久，直到event_del（）被调用。

请注意，使用event_assign（）请求您已经分配了事件结构。这样做通常需要您的代码依赖于结构的大小，并将创建可能与未来版本的Libevent不兼容。如果这似乎是一个坏主意，使用event_new（）和event_free（）。

参数：
ev		要修改的事件结构
base	ev应该附加的事件基础。
fd		要监视的文件描述符
event	期望的事件监视; 可以是EV_READ和/或EV_WRITE
fn		当事件发生时调用的回调函数
arg		一个要传递给回调函数的参数
返回：
如果成功，则为0，对无效参数为-1。

*/