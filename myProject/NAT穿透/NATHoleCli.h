#ifndef NATHOLECLI_H
#define NATHOLECLI_H
#include <list>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <pthread.h>
#include "UDPMessage.h"

class NATHoleCli{
private:
	UDPMessage *udpMess;
	char *serAddr;//服务器只有一个，登录后要保存ip
	int serPort;
	bool login;
	bool stop;
	/* 和自己 punch 的 client 和 p2p的server 进行会话保持（压力应该由发起人承担） */
	std::list<std::string> punchUsers;
	static const int userLen = 30;//存放ip和端口 如果将来user名增长了记得修改
public:
	enum STATU{ LOGIN, LOGACK, LOGOUT, LIST, PUNCH, SYN, ACK, SEND, QUIT, KEEPALIVE, PLIST };
	static const char *CMD[];
public:
	NATHoleCli(const char *ip, int port) :login(false), stop(false),serAddr(new char[16]){
		udpMess = new UDPMessage();
		udpMess->CreateSocket(ip, port, true);
	}
	~NATHoleCli(){
		delete udpMess;
		delete serAddr;
	}
	int splitCMD(std::string cmd, const char *spl, std::vector<std::string> &v){
		if(cmd.empty() || !spl)
			return 0;
		v.clear();
		char *p = strtok((char *)cmd.c_str(), spl);
		int i = 0;
		while (p){
			v.push_back(std::string(p));
			p = strtok(NULL, spl);
			++i;
		}
		return i;
	}
	bool AddUser(std::string user){
		for(auto u : punchUsers){
			if(u == user)
				return false;
		}
		punchUsers.push_back(user);
		return true;
	}
	bool DelUser(std::string user){
		for(auto it = punchUsers.begin(); it != punchUsers.end(); ++it){
			if(*it == user){
				punchUsers.erase(it);
				return true;
			}
		}
		return false;
	}
	//不用打印服务器(只是为了方便把服务器也归为这一类)
	void PrintPunchUsers(){
		std::string serverUser = std::string(serAddr) + " " + std::to_string(serPort);
		for(auto u : punchUsers){
			if(serverUser == u)
				continue;
			std::cout<<"("<<u<<")"<<std::endl;
		}
	}
	void Console() {
		std::string input;
		std::vector<std::string> v;
		while (1){
			std::cout << "<<<";
			getline(std::cin, input);
			if (input.empty())
				continue;
			//全部转化为小写（大小写不敏感）
			transform(input.begin(), input.end(), input.begin(), tolower);
			int num = splitCMD(input, " ", v);
			//必须先登录
			if(!login && (v[0] == CMD[LOGOUT] || v[0] == CMD[LIST] || v[0] == CMD[PUNCH] || v[0] == CMD[SEND])){
				std::cout << "you are not login" << std::endl;
				continue;
			}
			if (CMD[LOGIN] == v[0] && 3 == num){
				udpMess->write(v[1].c_str(), atoi(v[2].c_str()), CMD[LOGIN], strlen(CMD[LOGIN]));
			}
			else if (CMD[LOGOUT] == v[0] && 1 == num){
				udpMess->write(serAddr, serPort, CMD[LOGOUT], strlen(CMD[LOGOUT]));
				std::string user = std::string(serAddr) + " " + std::to_string(serPort);
				DelUser(user);
				login = false;
				memset(serAddr, 0, 16);
				serPort = -1;
			}
			else if (CMD[LIST] == v[0] && 1 == num){
				udpMess->write(serAddr, serPort, CMD[LIST], strlen(CMD[LIST]));
			}
			else if (CMD[PLIST] == v[0] && 1 == num){
				PrintPunchUsers();
			}
			else if (CMD[PUNCH] == v[0] && 3 == num){
				std::string sendBuf(CMD[PUNCH]);
				sendBuf = sendBuf + " " + v[1] + " " + v[2];
				//先给 ME 发
				udpMess->write(serAddr, serPort, sendBuf.c_str(), sendBuf.size());
				//再给 punch 发
				udpMess->write(v[1].c_str() , atoi(v[2].c_str()), "hole", 5);
			}
			else if (CMD[SEND] == v[0] && num > 3){
				std::string sendBuf(CMD[SEND]);
				for (int i = 3; i < num; ++i)
					sendBuf = sendBuf + " " + v[i];
				udpMess->write(v[1].c_str(), atoi(v[2].c_str()), sendBuf.c_str(), sendBuf.size());
				std::cout << sendBuf << std::endl;
			}
			else if (CMD[QUIT] == v[0] && 1 == num){
				udpMess->write(serAddr, serPort, CMD[LOGOUT], strlen(CMD[LOGOUT]));
				break;
			}
			else{
				Help();
			}
		}
		stop = true;
	}
	void Dispatch(){
		char *cmd = strtok(udpMess->readBuf, " ");
		if(!cmd){
			std::cout << "cmd = NULL " << udpMess->readBuf << std::endl; return;
		}
		//如果是keepAlive就不打印日志了
		if (strcmp(cmd, CMD[KEEPALIVE]) == 0)
			return;
		//ME -> A TO LOGACK
		if (strcmp(cmd, CMD[LOGACK]) == 0) {
			/* 保存服务器 ip port */
			strcpy(serAddr, udpMess->cliIP);
			serPort = udpMess->cliPort;
			/* 和服务器维持心跳 */
			std::string user = std::string(serAddr) + std::string(" ") + std::to_string(serPort);
			/* 登录状态改为true */
			login = true;
			if(AddUser(user))
				std::cout << "login success ！！ "<< user << std::endl;
			else
				std::cout << "login fail "<< user << std::endl;
		}
		// ME -> A list
		else if (strcmp(cmd, CMD[LIST]) == 0){
			char *list = strtok(NULL, "");//不切了,取剩下的
			std::cout << list << std::flush;
		}
		//A SYN B TO ASK A
		else if (strcmp(cmd, CMD[SYN]) == 0){
			char *otherAddr = strtok(NULL, " ");
			char *otherPort = strtok(NULL, " ");
			if (otherAddr == NULL || otherPort == NULL) {
				std::cout << "bad punch destination" << std::endl;
			}
			else {
				udpMess->write(otherAddr, atoi(otherPort), CMD[ACK], strlen(CMD[ACK]));
				std::cout << otherAddr << " " << otherPort <<" connecting me!!" << std::endl;
			}
		}
		//A recv ACK
		else if (strcmp(cmd, CMD[ACK]) == 0){
			std::string user = std::string(udpMess->cliIP) + std::string(" ") + std::to_string(udpMess->cliPort);
			if(AddUser(user))
				std::cout << "success punch a user" << std::endl;
			else
				std::cout << "repeat punch a user" << std::endl;
		}
		// A -> B
		else if (strcmp(cmd, CMD[SEND]) == 0){
			char *message = strtok(NULL, "");
			if (message)
				std::cout << "收到局域网消息：" << message << std::endl;
		}
		else{
			std::cout << cmd << std::endl;
		}
		std::cout<<"<<<"<<std::flush;
	}
	static void *Listen(void *argv){
		NATHoleCli *self = (NATHoleCli *)argv;
		while (!self->stop){
			self->udpMess->read(1024);
			self->Dispatch();
		}
	}
	static void *KeepAlive(void *argv){
		NATHoleCli *self = (NATHoleCli *)argv;
		if(!self){
			std::cout<< "KeepAlive error ！!"<<std::endl;
			return NULL;
		}
		char *ipPortStr = new char[userLen];
		//10秒一次心跳
		while (!self->stop){
			sleep(10);
			if(self->punchUsers.empty())
				continue;
			for(auto u : self->punchUsers){
				memset(ipPortStr, 0, userLen);
				strcpy(ipPortStr, u.c_str());//为啥要copy一次？？答：string的copy-on-write技术 这个bug真的是
				char *ip = strtok(ipPortStr, " ");
				char *portStr = strtok(NULL, " ");
				if(ip && portStr){
					int port = atoi(portStr);
					self->udpMess->write(ip, port, CMD[KEEPALIVE], strlen(CMD[KEEPALIVE]));
				}
				else
					std::cout<< "KeepAlive error ip prot "<< u <<std::endl;
			}
		}
		delete ipPortStr;
	}
	void Run(){
		pthread_t pid[2];
		if (0 != pthread_create(&pid[0], NULL, Listen, this)) {
			std::cout << "no Listen" << std::endl;
			return;
		}
		if (0 != pthread_create(&pid[1], NULL, KeepAlive, this)) {
			std::cout << "no KeepAlive" << std::endl;
			return;
		}
		std::cout << "client listenning" << std::endl;
		//监听键盘
		Console();
	}
	void Help() {
		const char *help_message = ""
			"Usage:"
			"\n\n login [host] [port] [name]"
			"\n     Login to p2p server."
			"\n\n logout"
			"\n     Logout from p2p server."
			"\n\n list"
			"\n     List all logged peer(s) of server"
			"\n\n plist"
			"\n     list all punched user of me."
			"\n\n punch [host] [port]"
			"\n     Send punch request directly to host:port(seen by server)"
			"\n     For example:"
			"\n         punch 192.168.1.110 52333"
			"\n     This will get a tunnel over NAT(s) to 192.168.1.110:52333 if successed"
			"\n\n send [host] [port] [message]:"
			"\n     Send [message] to peer which is already punched."
			"\n\n help:"
			"\n     Print this message."
			"\n\n quit: Quit the application.\n";
		std::cout << help_message << std::endl;
	}
};
const char *NATHoleCli::CMD[] = { "login", "logack", "logout", "list", "punch", "syn", "ack" , "send", "quit", "keepAlive", "plist" };
#endif