#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
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
		int res = recv(cliSocket, buf, sizeof(buf), 0);
		if (res > 0)
		{
			buf[res] = '\n';
			printf("东哥：%s",buf);
		}
	}
}

int main()
{
	WORD sockVersion = MAKEWORD(2, 2);//版本号
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockClient == INVALID_SOCKET)
	{
		return 0;
	}
	
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(19656);
	//serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//下面这4段话就是  域名转化为点分形式IP
	struct hostent *host = gethostbyname("chenmingdong666.6655.la");
	in_addr * iddr = (in_addr*)host->h_addr;
	unsigned long IPUL = iddr->s_addr;//直接得到了inet_addr(IP)
	char *IP = inet_ntoa(*iddr);//的到的是点分形式IP

	//serAddr.sin_addr.S_un.S_addr = inet_addr(IP);
	serAddr.sin_addr.S_un.S_addr = IPUL;
	if (connect(sockClient, (sockaddr *)&serAddr, sizeof(serAddr)))
	{
		printf("connect error !");
		closesocket(sockClient);
		return 0;
	}
	//连接成功后
	char buf[1024];
	CreateThread(0, 0, receive, (LPVOID)sockClient, 0, 0);
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		gets(buf);
		send(sockClient, buf, strlen(buf), 0);
	}
	closesocket(sockClient);
	WSACleanup();
	return 0;
}