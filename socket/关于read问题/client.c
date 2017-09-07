#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int sock;
	sock= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock<0){
		return 0;
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		return 0;
	}
	////////////////////////////////////////////////////////
	char *buf1 = "hello ";
	write(sock,buf1,strlen(buf1) + 1);
	printf("buf = %s\n",buf1);
	
	sleep(1);
	
	char *buf2 = "world ";
	write(sock,buf2,strlen(buf2) + 1);
	printf("buf = %s\n",buf2);
	
	sleep(2);
	
	char *buf3 = "陈明东";
	write(sock,buf3,strlen(buf3) + 1);
	printf("buf = %s\n",buf3);
	////////////////////////////////////////////////////////
	
	sleep(5);
	close(sock);
	printf("close\n");
}