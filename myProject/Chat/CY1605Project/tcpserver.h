#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "event.h"

class CTcpServer
{
public:
    CTcpServer(const char *ip, unsigned short port);
    ~CTcpServer();
    void run();
private:
    int mListenfd;
    struct event_base* mBase;
    
    friend void listen_cb(int fd, short event, void *lparg);
};


#endif