#ifndef MEMCACHED_H
#define MEMCACHED_H

#include <libmemcached/memcached.h>
#include <iostream>
using namespace std;

class CMemcached
{
public:
    CMemcached(char *ip, unsigned short port);
    ~CMemcached();
    
    char* queryKey(char *key);
    void saveValue(char *key, char *value);
private:
    memcached_st *memc;
    memcached_return rc;
    memcached_server_st *server;
};

#endif