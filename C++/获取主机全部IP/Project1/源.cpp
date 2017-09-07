#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>  
#include <winsock2.h>  

//连接Winsock库  
#pragma comment(lib, "ws2_32.lib")  

void main1()
{
	//调用WSAtartup初始化Winsock库  
	WSADATA wsaData;
	::WSAStartup(
		MAKEWORD(2, 2),//版本号为2.2  
		&wsaData
		);

	char szHost[256];//存放主机名的缓冲区  

	::gethostname(szHost, 256);//取得本地主机名称  

	hostent *pHost = ::gethostbyname(szHost);//通过主机名得到地址信息  

	//一个主机可能有多个网卡、多个IP、下面的代码输出所有的IP地址  
	in_addr addr;

	for (int i = 0;; i++)
	{
		//获得地址(网络字节)  
		char *p = pHost->h_addr_list[i];

		if (NULL == p)
		{
			break;//退出循环  
		}

		//将地址拷贝到in_addr结构体中  
		memcpy(&addr.S_un.S_addr, p, pHost->h_length);

		//将in_addr转换为主机字节序  
		char *strIP = ::inet_ntoa(addr);

		//打印IP地址  
		printf("本机IP[%d]: %s\n", i + 1, strIP);
	}

	//打印主机名  
	printf("主机名:%s\n", szHost);

	system("pause");
}