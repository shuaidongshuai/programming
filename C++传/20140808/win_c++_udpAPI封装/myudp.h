#pragma once
#ifndef LINUX
#include<WinSock2.h>
#else
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#endif
class myudp
{
private:
	SOCKET st;
public:
	myudp();
	~myudp();
	int socket_bind(int port);
	int socket_send(const char*IP, char buf[], int len, int port);
	int socket_recv(char IPbuf[], char buf[], int len);
};

