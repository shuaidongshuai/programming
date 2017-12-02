#ifndef SRMESSAGE_H
#define SRMESSAGE_H
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class UDPMessage{
public:
	//本机的socket
	int sockfd;
	//接收的buf
	int readSize;
	char *readBuf;
	//接收的用户信息
	char *cliIP;
	int cliPort;
public:
	UDPMessage() :sockfd(-1), readSize(-1), readBuf(NULL), cliIP(new char[16]){}
	~UDPMessage(){
		delete readBuf;
		delete cliIP;
	}
	bool CreateSocket(const char *ip, int port, bool isServer = false){
		if (-1 != sockfd)
			close(sockfd);
		int success = 0;
		struct sockaddr_in addr;
		socklen_t slen = sizeof(addr);
		memset(&addr, 0, slen);
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(ip);
		addr.sin_port = htons(port);
		do {
			sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (sockfd == -1){
				std::cout << "Failed to create socket " << ip << ":" << port << std::endl;
				break;
			}
			if (!isServer){
				success = 1;
				break;
			}
			if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
				std::cout << "Failed to bind " << ip << ":" << port << std::endl;
				break;
			}
			success = 1;

		} while (0);
		if (!success && sockfd != -1) {
			close(sockfd);
			sockfd = -1;
			return false;
		}
		return true;
	}
	int read(int size){
		if (readSize < size){
			char *newBuf = new char[size];
			char *temp = newBuf;
			newBuf = readBuf;
			readBuf = temp;
			readSize = size;
			delete newBuf;
		}
		struct sockaddr_in peer_addr;
		socklen_t slen = sizeof(peer_addr);
		memset(&peer_addr, 0, slen);
		memset(readBuf, 0, readSize);
		ssize_t rd_size = recvfrom(sockfd, readBuf, readSize, 0, (struct sockaddr*)&peer_addr, &slen);
		if (rd_size == -1){
			std::cout << "Read error" << std::endl;
			return -1;
		}
		memset(cliIP, 0, 16);
		strcpy(cliIP, inet_ntoa(peer_addr.sin_addr));
		cliPort = ntohs(peer_addr.sin_port);
		return rd_size;
	}
	int write(const char *ip, int port, const char *buf, int size){
		struct sockaddr_in peer_addr;
		socklen_t slen = sizeof(peer_addr);
		memset(&peer_addr, 0, slen);
		peer_addr.sin_family = AF_INET;
		peer_addr.sin_addr.s_addr = inet_addr(ip);
		peer_addr.sin_port = htons(port);
		
		ssize_t send_size = sendto(sockfd, buf, size, 0, (const struct sockaddr *)&peer_addr, slen);
		if (send_size == -1){
			std::cout << "Send ("<<ip<<":"<<port<<") error"<< std::endl;
			return -1;
		}
		return send_size;
	}
};
#endif