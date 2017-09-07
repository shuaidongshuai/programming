#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/if_ether.h>
//#include <linux/in.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_MAX 2048

int main(int argc, char *argv[])
{
	int sock, n_read, proto, portdst = 0, portsrc = 0, transfd;
	char buffer[BUFFER_MAX];
	char  *ethhead, *iphead, *tcphead, 
					 *udphead, *icmphead, *p, *q;
    char ipsrc[20], ipdst[20];
	struct sockaddr_in servaddr;
	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0)
    {
        fprintf(stdout, "create socket error\n");
        return 0;
    }
	
	while(1)
	{
		//n_read = read(sock, buffer, 2048);//read好像也可以
		n_read = recvfrom(sock, buffer, 2048, 0, NULL, NULL);
		/*
		14   6(dest)+6(source)+2(type or length)
		+
		20   ip header 
		+
		8   icmp,tcp or udp header
		= 42
		*/
		if(n_read < 42) 
		{
		  fprintf(stdout, "Incomplete header, packet corrupt\n");
		  continue;
		}
        
        ethhead = buffer;
        p = ethhead;
		q = p + 34;
		portdst = (q[2]<<8)&0XFF00 |  q[3]&0XFF;
		if(portdst != 9999)
			continue;
        int n = 0XFF;
		/*以太网数据链路层帧  前8个字节：目的mac地址，后8个字节：源mac地址*/
        printf("MAC: %.2X:%02X:%02X:%02X:%02X:%02X==>"
                           "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
        p[6]&n, p[7]&n, p[8]&n, p[9]&n, p[10]&n, p[11]&n,
        p[0]&n, p[1]&n, p[2]&n,p[3]&n, p[4]&n, p[5]&n);

        iphead = ethhead + 14;//ip数据报的头部
        p = iphead + 12;//原目标ip地址
        
		sprintf(ipsrc,"%d.%d.%d.%d",p[0]&0XFF, p[1]&0XFF, p[2]&0XFF, p[3]&0XFF);
		sprintf(ipdst,"%d.%d.%d.%d",p[4]&0XFF, p[5]&0XFF, p[6]&0XFF, p[7]&0XFF);
		printf("IP: %s => %s\n",ipsrc, ipdst);
		
		proto = (iphead + 9)[0];//协议
		p = iphead + 20;
		printf("Protocol: ");
		switch(proto)
		{
			case IPPROTO_ICMP: printf("ICMP\n");break;
			case IPPROTO_IGMP: printf("IGMP\n");break;
			case IPPROTO_IPIP: printf("IPIP\n");break;
			case IPPROTO_TCP :
			case IPPROTO_UDP : 
								printf("%s,", proto == IPPROTO_TCP ? "TCP": "UDP"); 
								//源端口 占2个字节 && 网络字节序(大端) && 需要把p[0]放到p[1]后面
								portsrc = (p[0]<<8)&0XFF00 |  p[1]&0XFF;
								portdst = (p[2]<<8)&0XFF00 |  p[3]&0XFF;
								printf("source port: %u,", portsrc);
								printf("dest port: %u\n", portdst);
								break;
			case IPPROTO_RAW : printf("RAW\n");break;
			default:printf("Unkown, please query in include/linux/in.h\n");
		}
		if(portdst == 9999)
		{
			if((transfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0)
			{
				printf("创建socket失败\n");
				exit(0);
			}
			
			//修改mac  52:54:00:D2:C6:BB
			p = buffer;
			p[0] = 0x52, p[1] = 0x54, p[2] = 0x00,p[3] = 0xD2, p[4] = 0xC6, p[5] = 0xBB;
			printf("MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",p[0]&n, p[1]&n, p[2]&n,p[3]&n, p[4]&n, p[5]&n);
			//修改ip  10.141.89.91  
			p = buffer + 26;
			//p[4] = 139, p[5] = 199, p[6] = 26, p[7] = 222;
			p[4] = 10, p[5] = 141, p[6] = 89, p[7] = 91;
			sprintf(ipdst,"%d.%d.%d.%d",p[4]&0XFF, p[5]&0XFF, p[6]&0XFF, p[7]&0XFF);
			printf("IP:%s\n",ipdst);
			
			bzero(&servaddr,sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			inet_pton(AF_INET,ipdst,&servaddr.sin_addr);
			servaddr.sin_port = htons(portdst);
			if(sendto(transfd, buffer, n_read, 0, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
			{
				printf("发送失败\n");
				printf("errno:%d\n",errno);
			}
		}
   }
}
/*
int sendto(int s, const void * msg, int len, unsigned int flags, const struct sockaddr * to, int tolen);

*/