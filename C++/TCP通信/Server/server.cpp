#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
//#include <thread>
//thread中也有bind，，socket中也有bind   这个时候我们不能用 using namespace std; 因为 thread 中的 bind 调用时 std::bind  默认会调用这个 而不会调用socket中的bind
#pragma comment(lib,"ws2_32.lib")

//DWORD WINAPI receive(
//	LPVOID lpThreadParameter
//	)
//{
//	char buf[1024];
//	SOCKET cliSocket = (SOCKET)lpThreadParameter;
//	while (1)
//	{
//		memset(buf, 0, sizeof(buf));
//		if (recv(cliSocket, buf, sizeof(buf), 0) <= 0)
//		{
//			std::cout << "没有接受到消息" << std::endl;
//			return;
//		}
//		std::cout << buf << std::endl;
//	}
//	closesocket(cliSocket);
//}
//DWORD WINAPI delivery(
//	LPVOID lpThreadParameter
//	)
//{
//	char buf[1024];
//	SOCKET cliSocket = (SOCKET)lpThreadParameter;
//	while (1)
//	{
//		std::cout << "本人： ";
//		std::cin.getline(buf, 1024);
//
//		/* send to client */
//		if (send(cliSocket, buf, sizeof(buf), 0) <= 0)
//		{
//			std::cout << "send error" << std::endl;
//			return;
//		}
//	}
//	//closesocket(cliSocket);
//}


int main11()
{
	/* init winsock */
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data));

	/* create a tcp socket */
	SOCKET serSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//创建一个结构体
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6666);
	addr.sin_addr.S_un.S_addr = htons(INADDR_ANY);//本机IP

	if (bind(serSocket, (sockaddr*)&addr, sizeof(addr))!=0)//绑定信息
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
	while (1)
	{
		printf("等待连接...\n");
		SOCKET cliSocket = accept(serSocket, (sockaddr*)&cliAddr, &len);//服务器accept一个 客服端地址（cliAddr），返回一个客服端socket
		if (cliSocket <= 0)
		{
			std::cout << "accept 失败" << std::endl;
			return -1;
		}
		printf("接受到一个连接：%s \r\n", inet_ntoa(cliAddr.sin_addr));

		//接收数据
		buf[0] = '\0';
		int res = recv(cliSocket, buf, sizeof(buf), 0);
		if (res > 0)
		{
			buf[res] = '\0';
			printf(buf);
		}
		//发送数据
		char* sendData = "你好啊，客服端！！\n";
		send(cliSocket, sendData, strlen(sendData), 0);
		closesocket(cliSocket);
	}

	/*CreateThread(0, 0, receive, (LPVOID)cliSocket, 0, 0);
	CreateThread(0, 0, delivery, (LPVOID)cliSocket, 0, 0);*/

	return 0;
}

