#include<stdio.h>
#include<arpa/inet.h>
int main()
{
	unsigned long addr = inet_addr("10.70.180.26");//主机 IP 转化为 32位 无符号整形 的网络字节序
	printf("%u\n",htonl(addr));						//  把网络字节序 转化为 本机字节序
	
	struct in_addr ipaddr;
	ipaddr.s_addr = addr;
	printf("%s\n",inet_ntoa(ipaddr));//把网络字节序转化为192.168..这种形式
	return 0;
}
