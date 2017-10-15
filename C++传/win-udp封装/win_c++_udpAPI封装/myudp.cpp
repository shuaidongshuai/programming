#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "myudp.h"
#include<string.h>
#include<stdio.h>
#ifndef LINUX
#include<WinSock2.h>
#else
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#endif
myudp::myudp()
{
#ifndef LINUX
	//初始化socket
	DWORD ver;//typedef unsigned long       DWORD;
	WSADATA wsaData;
	ver = MAKEWORD(1, 1);//告诉windows，用的是什么版本
	WSAStartup(ver, &wsaData);//第一步，必须调用这个函数
#endif
	//建立一个socket   1.指定socket用哪个协议
	st = socket(AF_INET,//用tcp/ip协议
		SOCK_DGRAM,//要用myudp协议
		0);//默认为0
}


myudp::~myudp()
{
#ifdef LINUX
	close(st);
#else
	closesocket(st);//关闭socket
	WSACleanup();//释放win socket资源
#endif
}

int myudp::socket_send(const char*IP, char buf[], int len, int port)
{
	struct  sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));//初始化
	addr.sin_family = AF_INET;//代表要用哪个Tcp/IP协议
	addr.sin_port = htons(port);//host to net short
	addr.sin_addr.s_addr = inet_addr(IP);

	size_t rc = sendto(st, buf, len + 1, 0, (struct sockaddr *)&addr, sizeof(addr));

	return rc;//发了多少出去
}

int myudp::socket_bind(int port)
{
	struct  sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//接收端不需要指定具体IP
	return bind(st, (struct sockaddr *)&addr, sizeof(addr));
}

int myudp::socket_recv(char IPbuf[], char buf[], int len)
{
	int rc = 0;
	struct sockaddr_in sendaddr;
	memset(&sendaddr, 0, sizeof(sendaddr));

#ifdef LINUX
	socklen_t len;
#else
	int addrlen;
#endif
	addrlen = sizeof(sendaddr);
	memset(buf, 0, addrlen);
	rc = recvfrom(st, buf, len, 0, (struct sockaddr *)&sendaddr, &addrlen);
	strcpy(IPbuf, inet_ntoa(sendaddr.sin_addr));
	return rc;
}
