#include "tcpserver.h"
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
using namespace std;
#include "controller.h"

//=========================================================
extern Controller gController;
//=========================================================
void client_cb(int fd, short event, void *lparg)
{
    char buffer[1024];
    int size = 0;
    
    size = recv(fd, buffer, 1024, 0);
    if(size <= 0)
    {
        cerr<<"client shutdowm exception! errno:"<<errno<<endl;
        return;
    }
    
    //把json字符串转给controller进行处理
    gController.process(buffer);
}

void listen_cb(int fd, short event, void *lparg)
{
    CTcpServer *pserver = (CTcpServer*)lparg;
    
    struct sockaddr_in client;
    socklen_t len=sizeof(client);
    int clientfd = accept(fd, (struct sockaddr*)&client, &len);
    if(clientfd == -1)
    {
        cerr<<"accept return invalid! errno:"<<errno<<endl;
        return;
    }
    
    cout<<"recv new client! ip:"<<inet_ntoa(client.sin_addr)
    <<" port:"<<ntohs(client.sin_port)<<endl;
    
    struct event *client_event = event_new(pserver->mBase, clientfd, EV_READ|EV_PERSIST, client_cb, lparg);  
    //把event事件放到reactor中
    event_add(client_event, NULL);
}


//=========================================================
CTcpServer::CTcpServer(const char *ip, unsigned short port)
{
    //创建，绑定，监听fd
    mListenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(mListenfd == -1)
    {
        cerr<<"mListenfd create fail! errno:"<<errno<<endl;
        exit(0);
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);
    
    if(-1 == bind(mListenfd, (struct sockaddr*)&server, sizeof(server)))
    {
        cerr<<"mListenfd bind fail! errno:"<<errno<<endl;
        exit(0);
    }
    
    if(-1 == listen(mListenfd, 20))
    {
        cerr<<"mListenfd listen fail! errno:"<<errno<<endl;
        exit(0);
    }
    
    //初始化libevent
    //创建libevent的reactor
    mBase = event_base_new();
    if(mBase == NULL)
    {
        cout<<"libevent init fail! errno:"<<errno<<endl;
        exit(-1);
    }
}
CTcpServer::~CTcpServer()
{
    //关闭监听套接字
    close(mListenfd);
    //关闭libevent
    //clean event and reator
    //event_free(listen_event);
    event_base_free(mBase);
}
void CTcpServer::run()
{
    cout<<"server is running..."<<endl;
    
    //启动tcp server
    //创建event事件
    struct event *listen_event = event_new(mBase, mListenfd, EV_READ|EV_PERSIST, listen_cb, this);  
    //把event事件放到reactor中
    event_add(listen_event, NULL);
    
    //start reator ->   dumplex    loop事件
    // event   reactor   dumplex   event_handler
    event_base_dispatch(mBase);
}