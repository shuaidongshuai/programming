#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 80
#define SERV_PORT 8000
#define IPADDR "127.0.0.1"

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd, n;
	//1
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, IPADDR, &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
	//2
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	while (fgets(buf, MAXLINE, stdin) != NULL) 
	{
		write(sockfd, buf, strlen(buf));
		n = read(sockfd, buf, MAXLINE);
		printf("---------------\n");
		if (n == 0)
			printf("服务器关闭.\n");
		else
			write(STDOUT_FILENO, buf, n);
	}
	close(sockfd);
	return 0;
}