#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <errno.h> 
#include <sys/socket.h>
#include <assert.h>
#include <signal.h>
#include <netinet/tcp.h> 
#include <map>
#include <list>
#include <iostream>

#ifndef Dong
#define NGINX_IPADDR	"127.0.0.1"
#define SERVER_IPADDR	"127.0.0.1"
#define NGINX_PORT	8000
#define BASE_SERVER_PORT 8001
#define MAXOPEN 4096
#define MAX_SERVER_NUM 5
#endif
