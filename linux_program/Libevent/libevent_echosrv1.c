/*
* libevent echo server example.
*/
#include
#include
#include
/* For inet_ntoa. */
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
* 这个结构是指定的客户端数据，这个例子中只指定了读事件对象。
*/
struct client {
	struct event ev_read;
};
/**
* 将一个socket 设置成非阻塞模式
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
* 这个函数当客户端的socket 可读时由libevent 调用
*/
void
on_read(int fd, short ev, void *arg)
{
	struct client *client = (struct client *)arg;
	u_char buf[8196];
	int len, wlen;
	len = read(fd, buf, sizeof(buf));
	if (len == 0) {
		/* 客户端断开连接，在这里移除读事件并且释放客户数据结
		构 */
		printf("Client disconnected.\n");
		close(fd);
		event_del(&client->ev_read);
		free(client);
		return;
	}
	else if (len < 0) {
		/* 出现了其它的错误，在这里关闭socket，移除事件并且释
		放客户数据结构 */
		printf("Socket failure, disconnecting client: %s", strerror(errno));
		close(fd);
		event_del(&client->ev_read);
		free(client);
		returreturn;
	}
	/* 为了简便，我们直接将数据写回到客户端。通常我们不能在非阻塞
	的应用程序中这么做，
	* 我们应该将数据放到队列中，等待可写事件的时候再写回客户端。
	*/
	wlen = write(fd, buf, len);
	if (wlen < len) {
		/* 我们没有把所有数据都写回。如果我们有适当的队列/缓存
		机制，
		* 我们能够在再次的可写事件中再次写入剩余的数据。因为
		这是一个简单的例子，
		* 我们仅仅舍去了没有写入的数据。 */
		printf("Short write, not all data echoed back to
			client.\n");
	}
}
/**
* 当有一个连接请求准备被接受时，这个函数将被libevent 调用。 */
void
on_accept(int fd, short ev, void *arg)
{
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	struct client *client;
	/* 接受新的连接 */
	client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd == -1) {
		warn("accept failed");
		return;
	}
	/* 设置客户端socket 为非阻塞模式。 */
	if (setnonblock(client_fd) < 0)
		warn("failed to set client socket non-blocking");
	/* 我们接受了一个新的客户，分配一个新的客户数据结构对象来保存
	这个客户的状态。 */
	client = calloc(1, sizeof(*client));
	if (client == NULL)
		err(1, "malloc failed");
	/* 设置读事件，libevent 将在客户端socket 可读时调用on_read 函
	数。
	* 我们也会我们也会不断的响应读事件，所以我们不用在每次读取时
	再次添加读事件。 */
	event_set(&client->ev_read, client_fd, EV_READ | EV_PERSIST,
		on_read,
		client);
	/* 设置的事件并没有激活，使用添加事件让其激活。 */
	event_add(&client->ev_read, NULL);
	printf("Accepted connection from %s\n",
		inet_ntoa(client_addr.sin_addr));
}
int
main(int argc, char **argv)
{
	int listen_fd;
	struct sockaddr_in listen_addr;
	int reuseaddr_on = 1;
	/* 接受连接请求的事件对象。 */
	struct event ev_accept;
	/* 初始化 libevent. */
	event_init();
	/* 创建我们监听的socket。 */
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
		err(1, "listen failed");
	if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR,
		&reuseaddr_on,
		sizeof(reuseaddr_on)) == -1)
		err(1, "setsockopt failed");
	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = INADDR_ANY;
	listen_addr.sin_port = htons(SERVER_PORT);
	if (bind(listen_fd, (struct sockaddr *)&listen_addr,
		sizeof(listen_addr)) < 0)
		err(1, "bind failed");
	if (listen(listen_fd, 5) < 0)
		err(1, "listen failed");
	/* 设置socket 为非阻塞模式，使用libevent 编程这是必不可少的。 */
	if (setnonblock(listen_fd) < 0)
		err(1, "failed to set server socket to non-blocking");
	/* 我们现在有了一个监听的socket，我们创建一个读事件，当有客户
	连接时，接收通知。 */
	event_set(&ev_accept, listen_fd, EV_READ | EV_PERSIST, on_accept,
		NULL);
	event_add(&ev_accept, NULL);
	/* 开始 libevent 的事件循环。 */
	event_dispatch();
	return 0;
}