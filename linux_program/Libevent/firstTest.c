#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <event.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT        8000
#define BACKLOG     5
#define MEM_SIZE    1024

struct event_base* base;
struct sockEvent
{
    struct event* readEvent;
    struct event* writeEvent;
    char* buffer;
};

void releaseSockEvent(struct sockEvent* ev)//delete from base and free it
{
    event_del(ev->readEvent);
    free(ev->readEvent);
    free(ev->writeEvent);
    free(ev->buffer);
    free(ev);
}

void handleWrite(int sock, short event, void* arg)
{
    char* buffer = (char*)arg;
    send(sock, buffer, strlen(buffer), 0);

    free(buffer);
}

void handldRead(int sock, short event, void* arg)
{
    struct event* writeEvent;
    int size;
    struct sockEvent* ev = (struct sockEvent*)arg;
    ev->buffer = (char*)malloc(MEM_SIZE);
    bzero(ev->buffer, MEM_SIZE);
    size = recv(sock, ev->buffer, MEM_SIZE, 0);
    printf("receive data:%s, size:%d\n", ev->buffer, size);
    if (size == 0) //client has send FIN
    {
        releaseSockEvent(ev);
        close(sock);
        return;
    }
    //add event to base to send the received data
    event_set(ev->writeEvent, sock, EV_WRITE, handleWrite, ev->buffer);
    event_base_set(base, ev->writeEvent);
    event_add(ev->writeEvent, NULL);
}

void handleAccept(int sock, short event, void* arg)//when new connection coming, calling this func
{
    struct sockaddr_in cli_addr;
    int newfd;
    socklen_t sinSize;
    struct sockEvent* ev = (struct sockEvent*)malloc(sizeof(struct sockEvent));
    ev->readEvent = (struct event*)malloc(sizeof(struct event));
    ev->writeEvent = (struct event*)malloc(sizeof(struct event));
    sinSize = sizeof(struct sockaddr_in);
    newfd = accept(sock, (struct sockaddr*)&cli_addr, &sinSize);
    //set the new coming connection event
    event_set(ev->readEvent, newfd, EV_READ|EV_PERSIST, handldRead, ev);
    event_base_set(base, ev->readEvent);
    event_add(ev->readEvent, NULL);
}

int main(int argc, char* argv[])
{
    struct sockaddr_in serverAddr;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    int on = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
    //memset(&serverAddr, 0, sizeof(serverAddr));
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
    listen(sock, BACKLOG);

    struct event listenEvent;
    base = event_base_new();//Create new EventBase
    event_set(&listenEvent, sock, EV_READ|EV_PERSIST, handleAccept, NULL);//conbine listenEvent and  it's callback function
    event_base_set(base, &listenEvent);
    event_add(&listenEvent, NULL);
    event_base_dispatch(base);//start base

    return 0;
}
/*
#define EV_READ		0x02  read
#define EV_PERSIST	0x10  persist¼á³Ö

*/