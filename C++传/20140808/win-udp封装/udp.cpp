#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
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

int socket_send(const char *IP)
{
#ifndef LINUX
	//初始化socket
	DWORD ver;//typedef unsigned long       DWORD;
	WSADATA wsaData;
	ver = MAKEWORD(1,1);//告诉windows，用的是什么版本
	WSAStartup(ver,&wsaData);//第一步，必须调用这个函数
#endif
	//建立一个socket   1.指定socket用哪个协议
	SOCKET st = socket(AF_INET,//用tcp/ip协议
		SOCK_DGRAM,//要用udp协议
		0);//默认为0
	struct  sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));//初始化
	addr.sin_family = AF_INET;//代表要用哪个Tcp/IP协议
	addr.sin_port = htons(8080);//host to net short
	addr.sin_addr.s_addr = inet_addr(IP);
	//printf("%d", inet_addr("127.0.0.1"));//1 00000000 00000000 01111111
										// 1.0.0.127
	char buf[1024];
	size_t rc;
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		gets(buf);
		rc = sendto(st, buf, strlen(buf) + 1, 0, (struct sockaddr *)&addr, sizeof(addr));
	}

#ifdef LINUX
	close(st);
#else
	closesocket(st);//关闭socket
	WSACleanup();//释放win socket资源
#endif

	return rc;//发了多少出去
}
int socket_recv()
{
#ifndef LINUX
	//初始化socket
	DWORD ver;//typedef unsigned long       DWORD;
	WSADATA wsaData;
	ver = MAKEWORD(1, 1);//告诉windows，用的是什么版本
	WSAStartup(ver, &wsaData);//第一步，必须调用这个函数
#endif

	SOCKET st = socket(AF_INET,SOCK_DGRAM,0);
	struct  sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//接收端不需要指定具体IP
	int rc = 0;
	if (bind(st, (struct sockaddr *)&addr, sizeof(addr)) != -1)//将端口号和程序绑定
	{
		char buf[1024];
		struct sockaddr_in sendaddr;
		memset(&sendaddr, 0, sizeof(sendaddr));

	#ifdef LINUX
		socklen_t len;
	#else
		int len;
	#endif

		len = sizeof(sendaddr);
		while (1)
		{
			memset(buf, 0, sizeof(buf));
			rc = recvfrom(st, buf, sizeof(buf), 0, (struct sockaddr *)&sendaddr,&len);
			printf("%s:\n%s\n",inet_ntoa(sendaddr.sin_addr), buf);
		}
	}

#ifdef LINUX
	close(st);
#else
	closesocket(st);//关闭socket
	WSACleanup();//释放win socket资源
#endif

	return rc;
}