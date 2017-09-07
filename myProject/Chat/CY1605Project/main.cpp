#include "tcpserver.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        cerr<<"command args is invalid! format: a./out ip port";
        exit(-1);
    }
    unsigned short port = atoi(argv[2]);
    CTcpServer server(argv[1], port);
    server.run();
    
    return 0;
}