/*
* libevent echo server example using buffered events.
*/
#include
#include
#include
#include
/* Required by event.h. */
#include
#include
#include
#include
#include
#include
#include
#include
/* Libevent. */
#include
/* Port to listen on. */
#define SERVER_PORT 5555
/**
* 指定用户数据的结构，也包含一列用户的指针。
*/
struct client {
	/* 客户端socket */
	int fd;
	/* 这个客户的 bufferedevent 对象。 */
	struct bufferevent *buf_ev;
};
/**
* 设置一个socket 为非阻塞模式。
*/
int
setnonblock(int fd)
{
	int flags;
	flags = fcntl(fd, F_GETFL);
	if (flags < 0)
		return flags;
	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0)
		return -1;
	return 0;
}
/**
* 当有数据可读时，libevent 调用这个函数
*/
void
buffered_on_read(struct bufferevent *bev, void *arg)
{
	/* 写回读缓冲区。注意 bufferevent_write_buffer 将逐渐发送完输
	入的数据
	* 所以我们调用它时，它就开始生效了。 */
	bufferevent_write_buffer(bev, bev->input);
}
/**
* 当写缓冲为0 时，libevent 调用这个函数。我们写出这个函数只是因为
libevent 需要，但是我们没有使用它。
*/
void
buffered_on_write(struct bufferevent *bev, void *arg)
{
}
/**
* 当基础的socket 描述符发生错误时，libevent 将调用这个函数。
*/
void
buffered_on_error(struct bufferevent *bev, short what, void *arg)
{
	struct client *client = (struct client *)arg;
	if (what & EVBUFFER_EOF) {
		/* 客户端断开连接，在这里移除读事件并释放客户数据结构。
		*/
		printf("Client disconnected.\n");
	}
	else {
		warn("Client socket error, disconnecting.\n");
	}
	bufferevent_free(client->buf_ev);
	close(client->fd);
	free(client);
}
/**
* 当有一个连接请求准备被接受时，这个函数将被libevent 调用。
*/
void
on_accept(int fd, short ev, void *arg)
{
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	struct client *client;
	client_fd = accept(fd, (struct sockaddr *)&client_addr,
		&client_len);
	if (client_fd < 0) {
		warn("accept failed");
		return;
	}
	/* 设置客户端socket 为非阻塞模式。 */
	if (setnonblock(client_fd) < 0)
		warn("failed to set client socket non-blocking");
	/* 我们接受一个新的客户，创建一个客户数据结构对象。 */
	client = calloc(1, sizeof(*client));
	if (client == NULL)
		err(1, "malloc failed");
	client->fd = client_fd;
	/* 创建 buffered 事件。
	*
	* 第一个参数是引起事件的文件描述符，这里是客户端socket。
	*
	* 第二个参数是一个回调函数，当数据已经被socket 读取并且对程序
	有效时，它被调用。
	*
	* 第三个参数是一个回调函数，当写缓冲区到达最小值时，它被调用。
	* 这通常意味着，当写入缓冲区长度为0 时，这个回调函数将被调用。
	* 它必须被定义，但是实际上你可以在这个回调函数中不做任何处理。
	*
	* 第四个参数是一个回调函数，当有socket 错误发生时，它被调用。
	* 在这里你可以探测客户端断开连接，或者其它的错误。
	*
	* 第五个参数用来存储一个将会传递给各个回调函数的参数。我们在
	这里存储客户数据对象。
	*/
	client->buf_ev = bufferevent_new(client_fd, buffered_on_read,
		buffered_on_write, buffered_on_error, client);
	/* 我们必须在回调函数被调用前，使它有效。 */
	bufferevent_enable(client->buf_ev, EV_READ);
	printf("Accepted connection from %s\n",
		inet_ntoa(client_addr.sin_addr));
}
int
main(int argc, char **argv)
{
	int listen_fd;
	struct sockaddr_in listen_addr;
	struct event ev_accept;
	int reuseaddr_on;
	/* 初始化 libevent. */
	event_init();
	/* 创建我们的监听socket。 */
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
		err(1, "listen failed");
	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = INADDR_ANY;
	listen_addr.sin_port = htons(SERVER_PORT);
	if (bind(listen_fd, (struct sockaddr *)&listen_addr,
		sizeof(listen_addr)) < 0)
		err(1, "bind failed");
	if (listen(listen_fd, 5) < 0)
		err(1, "listen failed");
	reuseaddr_on = 1;
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on,
		sizeof(reuseaddr_on));
	/* 设置socket 为非阻塞模式，这种与libevent 编程时是必须的。 */
	if (setnonblock(listen_fd) < 0)
		err(1, "failed to set server socket to non-blocking");
	/* 我们现在有了一个监听socket，我们创建一个读事件，以便在有客
	户连接请求时能够接收到通知。 */
	event_set(&ev_accept, listen_fd, EV_READ | EV_PERSIST, on_accept,
		NULL);
	event_add(&ev_accept, NULL);
	/* 开始事件循环。 */
	event_dispatch();
	return 0;
}