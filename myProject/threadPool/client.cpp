#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;

#define MAXLINE 100
#define IPADDR "127.0.0.1"
#define SERV_PORT 8000

void *run(void *argv){
	struct sockaddr_in servaddr;
	char buf[1024] = "hello dong";
	int sockfd;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		cout<<"socket error"<<endl;
		return 0;
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,IPADDR,&servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
	
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1){
		cout<<"connect error"<<endl;
		return 0;
	}
	write(sockfd,buf,strlen(buf));
	memset(buf, 0, 1024);
	read(sockfd,buf,1024);
	cout<<"收到："<<buf<<endl;
	close(sockfd);
}

int main(){
	//模仿高并发
	pthread_t pthreads[20];
	for(int i = 0; i < 20; ++i){
		if(pthread_create(pthreads + i, 0, run, 0)){
			cout<<"线程创建失败:"<<pthreads[i]<<endl;
		}
		if(pthread_detach( pthreads[i])){
            cout<<"pthread_detach失败:"<<pthreads[i]<<endl;
        }
	}
	cin.get();
}