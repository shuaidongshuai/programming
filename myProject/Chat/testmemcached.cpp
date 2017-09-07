#include <iostream>
#include <string.h>
using namespace std;
#include <libmemcached/memcached.h>
//NoSQL memcached    /    redis
int main()
{
    memcached_st *memc = NULL;
    memcached_return rc;
    memcached_server_st *servers = NULL;
    time_t expiration = 0;
    uint32_t flags = 0;
    
    memc = memcached_create(NULL);
    servers = memcached_server_list_append(NULL, "127.0.0.1", 6000, &rc);
    rc = memcached_server_push(memc, servers);
    
    string key = "helloworld!!!";
    string value = "1234   56";
    size_t value_length = value.length();
    size_t key_length = key.length();
    
    //Get data
    cout<<"memcached get pwd..."<<endl;
    char* result = memcached_get(memc, key.c_str(), key_length, &value_length, &flags, &rc);
    if(rc == MEMCACHED_SUCCESS)
    {
        cout<<"Get pwd: "<<result<<" successful!"<<endl;
    }
    else
    {
        cout<<rc<<endl;
        cout<<"get pwd fail..."<<endl;
    }
    
    cout<<"get pwd from db, save to memcached..."<<endl;
    rc = memcached_set(memc, key.c_str(), key.length(), value.c_str(), value.length(), expiration, flags);
    if(rc == MEMCACHED_SUCCESS)
    {
        cout<<"Save data: "<<value<<" successful!"<<endl;
    }
    else
    {
        cout<<rc<<endl;
        cout<<"set pwd fail..."<<endl;
    }
 
    cout<<"memcached get pwd..."<<endl;
    result = memcached_get(memc, key.c_str(), key_length, &value_length, &flags, &rc);
    if(rc == MEMCACHED_SUCCESS)
    {
        cout<<"Get pwd: "<<result<<" successful!"<<endl;
    }
    else
    {
        cout<<"rc:"<<rc<<endl;
        cout<<"Get pwd fail..."<<endl;
    }
    
    //free
    memcached_free(memc);
    
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
char* getServerPort(unsigned short cport)
{
	char portbuf[6]={0};
	sprintf(portbuf, "%d", cport);

	/*定义hash函数*/
	CHashFun * func = new CMD5HashFun();
	/*创建一致性hash对象*/
	CConHash * conhash = new CConHash(func);

	/*定义CNode*/
	CNode_s * node1 = new CNode_s("server1",50,"8000");
	CNode_s * node2 = new CNode_s("server2",80,"8001");
	CNode_s * node3 = new CNode_s("server3",20,"8002");
	//CNode_s * node4 = new CNode_s("machineD",100,"10.3.0.204");

	conhash->addNode_s(node1);
	conhash->addNode_s(node2);
	conhash->addNode_s(node3);

	CNode_s *node = conhash->lookupNode_s(portbuf);
	return node->getIden();
}

int main()
{
	int ports[100];
	for(int i=0; i<100; ++i)
	{
		ports[i] = rand()%40000+1024;
	}

	int server[3]={0};
	for(int i=0; i<100; ++i)
	{
		if(strcmp(getServerPort(ports[i]), "server1") == 0)
		{
			server[0]++;
		}
		else if(strcmp(getServerPort(ports[i]), "server2") == 0)
		{
			server[1]++;
		}
		else
		{
			server[2]++;
		}
	}
	return 0;
}
//b班的同学，友情提醒，memcached的key字段不允许有空格，否则接口调用就挂掉了
