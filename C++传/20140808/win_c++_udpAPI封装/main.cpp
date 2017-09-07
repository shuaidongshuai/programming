#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"myudp.h"
using namespace std;

int main(int argc, char **args)
{
	if (argc > 1)
	{
		myudp u;
		char buf[1024];
		while (1)
		{
			memset(buf, 0, sizeof(buf));
			gets(buf);
			u.socket_send(args[1], buf, strlen(buf), 8080);
		}
	}
	else
	{
		myudp u;
		char buf[1024];
		char IPbuf[100];
		if (u.socket_bind(8080) != -1)
		{
			while (1)
			{
				memset(buf, 0, sizeof(buf));
				memset(IPbuf, 0, sizeof(IPbuf));
				u.socket_recv(IPbuf, buf, sizeof(buf));
				printf("%s: %s\n", IPbuf, buf);
			}
		}
	}
	return 0;
}