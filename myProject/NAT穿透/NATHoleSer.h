#ifndef NATHOLESER_H
#define NATHOLESER_H
#include <cstring>
#include <list>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "UDPMessage.h"
class NATHoleSer{
	std::list<std::string> users;
	UDPMessage *udpMess;
	enum STATU{ LOGIN , LOGACK, LOGOUT, LIST, PUNCH, SYN, KEEPALIVE };
	static const char *CMD[];
public:
	NATHoleSer(const char *ip, int port){
		udpMess = new UDPMessage();
		udpMess->CreateSocket(ip, port, true);
	}
	~NATHoleSer(){
		delete udpMess;
	}
	void Dispatch(){
		//如果是keepAlive就不打印日志了
		if (strcmp(udpMess->readBuf, CMD[KEEPALIVE]) == 0)
			return;
		//日志
		std::string user = std::string(udpMess->cliIP) + " " + std::to_string(udpMess->cliPort);
		std::cout << "收到["<<user<<"]" << udpMess->readBuf << std::endl;
		//MD strtok会改变原串(变成第一个切分串)
		char *cmd = strtok(udpMess->readBuf, " ");
		if (strcmp(cmd, CMD[LOGIN]) == 0) {
			bool repeatUser = false;
			for(auto u : users){
				if(u == user){
					repeatUser = true;
					break;
				}
			}
			if(!repeatUser)
				users.push_back(user);
			//登录成功给一个回应
			udpMess->write(udpMess->cliIP, udpMess->cliPort, CMD[LOGACK], strlen(CMD[LOGACK]));
			//日志
			std::cout << "发送["<<user<<"]"<<CMD[LOGACK]<<std::endl;
		}
		else if (strcmp(cmd, CMD[LOGOUT]) == 0) {
			for (auto it = users.begin(); it != users.end(); ++it){
				if (*it == user){
					std::cout<<"LOGOUT["<<*it<<"]"<<std::endl;
					users.erase(it);
					break;
				}
			}
		}
		else if (strcmp(cmd, CMD[LIST]) == 0) {
			std::string sendMes(CMD[LIST]);
			sendMes += " ";
			for (auto it = users.begin(); it != users.end(); ++it){
				if (*it == user)
					sendMes += "[☆" + *it + "☆]\n";
				else
					sendMes += "[" + *it + "]\n";
			}
			int size = udpMess->write(udpMess->cliIP, udpMess->cliPort, sendMes.c_str(), sendMes.size());
			//日志
			std::cout << "发送["<<user<<"]total:"<<size<<"\n"<<sendMes<< std::flush;
		}
		else if (strcmp(cmd, CMD[PUNCH]) == 0) {
			char *otherAddr = strtok(NULL, " ");
			char *otherPort = strtok(NULL, " ");
			if (otherAddr == NULL || otherPort == NULL) {
				std::cout << "bad punch destination" << std::endl;
			}
			else {
				//A -> ME FOR B | ME -> B TO ACK A
				std::string request = std::string(CMD[SYN]) + " " + user;
				udpMess->write(otherAddr, atoi(otherPort), request.c_str(), request.size() + 1);
				//日志
				std::cout << "发送["<<otherAddr<<" "<<otherPort<<"]"<<request<<std::endl;
			}
		}
	}
	void Run(){
		while (1){
			udpMess->read(1024);
			Dispatch();
		}
	}
};
const char *NATHoleSer::CMD[] = { "login", "logack", "logout", "list", "punch", "syn", "keepAlive" };
#endif