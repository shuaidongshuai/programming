#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <event.h>
#include <iostream>
#include <string>
#include <json/json.h>
#include <string.h>
#include "../public.h"
using namespace std;

int clientfd;
pthread_t tid;

void* threadproc(void *lparg)
{
    //该线程启动循环接收模式，不断接收服务器发送过来的消息
}

void doLogin()
{
    char name[20]={0};
    char pwd[20]={0};
    
    cout<<"name:";
    gets(name);
    cout<<"pwd";
    gets(pwd);
    
    Json::Value json;
    json["msgtype"] = MSG_TYPE_LOGIN;
    json["name"] = name;
    json["pwd"] = pwd;
    
    send(clientfd, json.toStyledString().c_str(),
        strlen(json.toStyledString().c_str()), 0);
        
    //recv等待服务器返回的结果
    
    //结果如果正确，马上启动接收线程
    pthread_create(&tid, NULL, threadproc, NULL);
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        cerr<<"command args is invalid! format: a./out ip port";
        exit(-1);
    }
    unsigned short port = atoi(argv[2]);
    char ip[20];
    strcpy(ip, argv[1]);
    
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1)
    {
        cerr<<"clientfd create fail! errno:"<<errno<<endl;
        exit(0);
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);
    
    if(-1 == connect(clientfd, (struct sockaddr*)&server, sizeof(server)))
    {
        cerr<<"connect fail! errno:"<<errno<<endl;
        exit(0);
    }
    
    int choice = 0;
    while(true)
    {
        cout<<"================"<<endl;
        cout<<"1.login"<<endl;
        cout<<"2.register"<<endl;
        cout<<"3.exit"<<endl;
        cout<<"================"<<endl;
        cout<<"choice:";
        cin>>choice;
        getchar();  // \n
        
        switch(choice)
        {
            case 1:
            doLogin();
            break;
        }
    }
    
    return 0;
}