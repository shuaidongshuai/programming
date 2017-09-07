#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<errno.h>  
#include<unistd.h>  
  
#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
  
#include<event.h>  
#include<event2/util.h>  
  
int tcp_connect_server(const char* server_ip, int port);  
void cmd_msg_cb(int fd, short events, void* arg);  
void socket_read_cb(int fd, short events, void *arg);  
  
int main(int argc, char** argv)  
{
    if( argc < 3 )  
    {  
        printf("please input 2 parameter\n");  
        return -1;  
    }  
  
    //两个参数依次是服务器端的IP地址、端口号  
    int sockfd = tcp_connect_server(argv[1], atoi(argv[2]));  
    if( sockfd == -1)  
    {  
        perror("tcp_connect error ");  
        return -1;  
    }  
  
    printf("connect to server successful\n");  
  
    struct event_base* base = event_base_new();//初始化
  
    struct event *ev_sockfd = event_new(base, 
										sockfd,  EV_READ | EV_PERSIST,//这两个都是参数
                                        socket_read_cb,//回调函数（这个程序中，用来读）
										NULL);//这个也是参数
	/*
		typedef void (*event_callback_fn)(evutil_socket_t, short, void *);//回调函数类型
event_new(struct event_base *base, evutil_socket_t fd, short events, void (*cb)(evutil_socket_t, short, void *), void *arg)
		#define EV_TIMEOUT 0x01 	定时事件
		#define EV_READ 0x02 		I/O事件
		#define EV_WRITE 0x04 		I/O事件
		#define EV_SIGNAL 0x08 		信号
		#define EV_PERSIST 0x10 	永久事件
		#define EV_ET 0x20 			边沿触发
	*/
    event_add(ev_sockfd, NULL);  
    /*
	虽然已经初始化了事件，但是该事件并不会被触发，原因在于我们并没有激活该事件。
	`event_add`函数提供了激活事件的功能。int event_add(struct event *ev, const struct timeval *tv);
	如果是一个（non-pending）未注册`ev`，调用`event_add`函数会注册该事件（变为pending状态）。
	如果是一个（pending）注册过的`ev`，调用该函数会在tv时间后重新注册该事件。成功返回0，失败返回-1。
	*/
    //监听终端输入事件  
    struct event* ev_cmd = event_new(base, STDIN_FILENO,  
                                      EV_READ | EV_PERSIST,
									  cmd_msg_cb, //回调函数（这个程序中，用来写）
                                      (void*)&sockfd);  
	/*
		STDIN_FILENO 就是标准输入设备（一般是键盘）的文件描述符。
	*/
    event_add(ev_cmd, NULL);  
	
    event_base_dispatch(base);//循环监听
	
    printf("finished \n");  
    return 0;  
}  
  
void cmd_msg_cb(int fd, short events, void* arg)  
{  
    char msg[1024];  
  
    int ret = read(fd, msg, sizeof(msg));//从键盘上读，平时我是用fgets来读的 
    if( ret <= 0 )  
    {  
        perror("read fail ");  
        exit(1);
    }
  
    int sockfd = *((int*)arg);  
  
    //把终端的消息发送给服务器端  
    //为了简单起见，不考虑写一半数据的情况  
    write(sockfd, msg, ret);  
}  
  
  
void socket_read_cb(int fd, short events, void *arg)  
{  
    char msg[1024];  
  
    //为了简单起见，不考虑读一半数据的情况  
    int len = read(fd, msg, sizeof(msg)-1);  
    if( len <= 0 )  
    {  
        perror("read fail ");  
        exit(1);  
    }  
  
    msg[len] = '\0';  
  
    printf("recv %s", msg);  
}  
  
int tcp_connect_server(const char* server_ip, int port)  
{  
    int sockfd, status, save_errno;  
    struct sockaddr_in server_addr;  
  
    memset(&server_addr, 0, sizeof(server_addr) );  
  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_port = htons(port);  
    status = inet_aton(server_ip, &server_addr.sin_addr);//inet_aton是一个改进的方法来将一个字符串IP地址转换为一个32位的网络序列IP地址。
  
    if( status == 0 ) //the server_ip is not valid value  
    {  
        errno = EINVAL;  
        return -1;  
    }
  
    sockfd = ::socket(AF_INET, SOCK_STREAM, 0);  
    if( sockfd == -1 )  
        return sockfd;  
  
  
    status = ::connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr) );  
  
    if( status == -1 )  
    {  
        save_errno = errno;  
        ::close(sockfd);  
        errno = save_errno; //the close may be error  
        return -1;  
    }  
  
    evutil_make_socket_nonblocking(sockfd);  
  
    return sockfd;  
}
/*
evutil_make_socket_nonblocking(evutil_socket_t fd)
{
#ifdef WIN32
	{
		u_long nonblocking = 1;
		if (ioctlsocket(fd, FIONBIO, &nonblocking) == SOCKET_ERROR) {
			event_sock_warn(fd, "fcntl(%d, F_GETFL)", (int)fd);
			return -1;
		}
	}
#else
	{
		int flags;
		if ((flags = fcntl(fd, F_GETFL, NULL)) < 0) {
			event_warn("fcntl(%d, F_GETFL)", fd);
			return -1;
		}
		if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
			event_warn("fcntl(%d, F_SETFL)", fd);
			return -1;
		}
	}
#endif
	return 0;
}

typedef void (*event_callback_fn)(evutil_socket_t, short, void *);//回调函数类型
struct event *event_new(struct event_base *base, evutil_socket_t fd, short events, void (*cb)(evutil_socket_t, short, void *), void *arg)
{
	struct event *ev;
	ev = mm_malloc(sizeof(struct event));
	if (ev == NULL)
		return (NULL);
	if (event_assign(ev, base, fd, events, cb, arg) < 0) {
		mm_free(ev);
		return (NULL);
	}
	return (ev);
}



int event_assign(struct event *ev, struct event_base *base, evutil_socket_t fd, short events, void (*callback)(evutil_socket_t, short, void *), void *arg)
{
	if (!base)
		base = current_base;

	_event_debug_assert_not_added(ev);

	ev->ev_base = base;

	ev->ev_callback = callback;
	ev->ev_arg = arg;
	ev->ev_fd = fd;
	ev->ev_events = events;
	ev->ev_res = 0;
	ev->ev_flags = EVLIST_INIT;
	ev->ev_ncalls = 0;
	ev->ev_pncalls = NULL;

	if (events & EV_SIGNAL) {
		if ((events & (EV_READ|EV_WRITE)) != 0) {
			event_warnx("%s: EV_SIGNAL is not compatible with "
			    "EV_READ or EV_WRITE", __func__);
			return -1;
		}
		ev->ev_closure = EV_CLOSURE_SIGNAL;
	} else {
		if (events & EV_PERSIST) {
			evutil_timerclear(&ev->ev_io_timeout);
			ev->ev_closure = EV_CLOSURE_PERSIST;
		} else {
			ev->ev_closure = EV_CLOSURE_NONE;
		}
	}

	min_heap_elem_init(ev);

	if (base != NULL) {
		//默认情况下，我们把新的事件放在中间优先级
		ev->ev_pri = base->nactivequeues / 2;
	}

	_event_debug_note_setup(ev);

	return 0;
}
*/