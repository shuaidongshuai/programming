#include <stdio.h>  
#include <unistd.h>  
#include <strings.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <netdb.h>  
#include <string>  
#include <iostream>  
#include "proto/people.pb.h"
#include "proto/test.pb.h"
#include "proto/test2.pb.h"
#include "proto/test3.pb.h"  

#define HOST "localhost"  
#define PORT 8888  
#define MAXDATASIZE 100  
  
using namespace std;  
  
int main(int argc, char ** argv)  
{  
	int fd, numbytes;  
	char buf[MAXDATASIZE];  
	struct hostent *he;  
	struct sockaddr_in server;  

	if (argc != 2) {  
		printf("Usage: %s \"COMMAND\"\n",argv[0]);  
		exit(0);  
	}   

	he = gethostbyname(HOST);  
	fd = socket(AF_INET, SOCK_STREAM, 0);  
	bzero(&server, sizeof(server));  
	server.sin_family = AF_INET;  
	server.sin_port = htons(PORT);  
	server.sin_addr = *((struct in_addr *)he->h_addr);  

	connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));  

	send(fd, argv[1], 20, 0);

	numbytes = recv(fd, buf, MAXDATASIZE, 0);  
	buf[numbytes] = '\0';  
	string data = buf;  
	//测试别的数据结构来接收
	Test t;
	bool r = t.ParseFromString(data);  
	if(!r){
		cout<<"不是Test类型数据"<<endl;
	}
	demo::People p;
	bool res = p.ParseFromString(data);  
	if(!res){
		cout<<"数据不完整"<<endl;
	}else{
		cout << "People: " << endl;  
		cout << "Name: " << p.name() << endl;  
		cout << "ID: " << p.id() << endl;  
		cout << "Email: " << p.email() << endl;  
	}
	
	//测试空protobuf	结论：如果是空的protobuf 解析出来都是true
	// Test2 t2;
	// bool r2 = t2.ParseFromString(data);  
	// if(!r2){
		// cout<<"不是Test2类型数据"<<endl;
	// }
	// cout<<"是Test2类型数据"<<endl;
	// Test3 t3;
	// bool r3 = t3.ParseFromString(data);  
	// if(!r3){
		// cout<<"不是Test3类型数据"<<endl;
	// }
	// cout<<"是Test3类型数据"<<endl;
	
	close(fd);  
	return 0;  
}