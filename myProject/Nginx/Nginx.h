class Nginx
{
public:
	static int checkserverfd[5];
public:
	void process(int sockfd);
	void sendtoServer(int clientfd);
	char* receivefromServer();
	static void connectServer();
	static void setnonblocking(int fd);
};

