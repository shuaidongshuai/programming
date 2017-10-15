#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

#include "src/threadPool.h"
using namespace std;

class Server{
public:
	void init(int confd, struct sockaddr_in cliaddr){
		this->sockfd = confd;
		this->cliaddr = cliaddr;
	}
	void run(){
		//简单的处理流程-----1.读 2.休眠(处理过程) 3.回写
		int buf[1024];//简单处理了，就当最大不超过1024
		int len = read(sockfd, buf, sizeof(buf));
		if(0 == len){
			cout<<"客户端退出"<<endl;
			return;
		}
		cout<<"client: "<<buf<<endl;
		sleep(1);
		const char *ret = "I recved your request";
		write(sockfd, ret, strlen(ret) + 1);
	}
private:
	int sockfd;
	struct sockaddr_in cliaddr;
};

int main(){
	int listenfd;
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return 0;
	}
	int reuse = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        return -1;
    }
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(8000);
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)	{
		cout<<"绑定失败"<<endl;
		return 0;
	}
	if(listen(listenfd, 1024)<0){
		cout<<"监听失败"<<endl;
		return 0;
	}
	socklen_t cliaddrLen = sizeof(cliaddr);
	Server *user = new Server[1024];
	ThreadPool<Server> *pool = new ThreadPool<Server>();
	while(1){
		int confd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrLen);
		if(confd < 0){
			cout<<"confd = "<<confd<<endl;
		}
		user[confd].init(confd, cliaddr);
		pool->append(user + confd);
	}
}