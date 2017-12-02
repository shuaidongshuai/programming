#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define LOG_TRACE(format, args...) fprintf(stdout, format"\n", ##args)
#define LOG_ERROR(format, ...) fprintf(stderr, format" (%s)\n", ##__VA_ARGS__, strerror(errno))

typedef struct endpoint{
	char ip[16];
    int port;
}endpoint;

int udp_send(int sockfd, const endpoint *dest, const char *data)
{
    struct sockaddr_in peer_addr;
    socklen_t slen = sizeof(peer_addr);
    memset(&peer_addr, 0, slen);
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = inet_addr(dest->ip);
    peer_addr.sin_port = htons(dest->port);
    ssize_t send_size = sendto(sockfd, data, strlen(data), 0, (const struct sockaddr *)&peer_addr, slen);
    if(send_size == -1)
        LOG_ERROR("Send error");
    LOG_TRACE("向(%s:%d) 发送 %s\n",dest->ip, dest->port ,data);
    return send_size;
}
int udp_receive(int sockfd, endpoint *from, char *data)
{
    struct sockaddr_in peer_addr;
    socklen_t slen = sizeof(peer_addr);
    memset(&peer_addr, 0, slen);
    ssize_t rd_size = recvfrom(sockfd, data, 1024, 0, (struct sockaddr*)&peer_addr, &slen);
    if(rd_size == -1)
        LOG_ERROR("Read error");
    else
    {
        const char *ip = inet_ntoa(peer_addr.sin_addr);
        int port = peer_addr.sin_port;
        strncpy(from->ip, ip, INET_ADDRSTRLEN);
        from->port = ntohs(port);
    }
	LOG_TRACE("收到(%s:%d) %s\n",from->ip, from->port ,data);
    return rd_size;
}

int main(int argc, char **argv){
	if(argc != 3){
		printf("%s ip port", argv[0]);
		return 0;
	}
	struct  sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));//初始化
	addr.sin_family = AF_INET;//代表要用哪个Tcp/IP协议
	addr.sin_port = htons(atoi(argv[2]));//host to net short
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd == -1){
		LOG_ERROR("socket error");
		return 0;
	}
	if( bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0 ) {
		LOG_ERROR("Failed to bind");
		return 0;
	}
			
	char buf[1024];
    endpoint ep;
    ssize_t read_size = 0;
	
	memset(buf, 0, 1024);
    while(1)
    {
		udp_receive(sockfd, &ep, buf);
        udp_send(sockfd, &ep, buf);
    }
	close(sockfd);
}