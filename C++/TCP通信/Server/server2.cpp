#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

DWORD WINAPI receive(
	LPVOID lpThreadParameter
	)
{
	char buf[1024];
	SOCKET cliSocket = (SOCKET)lpThreadParameter;
	while (1)
	{
		//接收数据
		memset(buf, 0, sizeof(buf));
		int res = recv(cliSocket, buf, sizeof(buf)-1, 0);
		if (res > 0)
		{
			buf[res] = '\n';
			//buf[res+1] = '\0';  因为我们前面 memset全是0所以这里不用加
			printf("小马：%s", buf);
		}
	}
}

int main()
{
	/* init winsock */
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data));

	/* create a tcp socket */
	SOCKET serSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//创建一个结构体
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.S_un.S_addr = htons(INADDR_ANY);//本机IP

	if (bind(serSocket, (sockaddr*)&addr, sizeof(addr)) != 0)//绑定信息
	{
		std::cout << "绑定失败" << std::endl;
		return -1;
	}
	if (listen(serSocket, 5) != 0)
	{
		std::cout << "监听失败" << std::endl;
		return -1;
	}

	/* waiting for connection */
	SOCKADDR_IN cliAddr;
	int len = sizeof(cliAddr);
	char buf[1024];
	
	printf("等待连接...\n");
	SOCKET cliSocket = accept(serSocket, (sockaddr*)&cliAddr, &len);//服务器accept一个 客服端地址（cliAddr），返回一个客服端socket
	if (cliSocket <= 0)
	{
		std::cout << "accept 失败" << std::endl;
		return -1;
	}

	printf("接受到一个连接：%s \r\n", inet_ntoa(cliAddr.sin_addr));
	CreateThread(0, 0, receive, (LPVOID)cliSocket, 0, 0);
	while (1)
	{
		//发送数据
		memset(buf, 0, sizeof(buf));
		gets(buf);
		send(cliSocket, buf, strlen(buf), 0);
	}
	closesocket(cliSocket);

	/*CreateThread(0, 0, receive, (LPVOID)cliSocket, 0, 0);
	CreateThread(0, 0, delivery, (LPVOID)cliSocket, 0, 0);*/

	return 0;
}

