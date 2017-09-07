#include "mysqlserver.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

CMySqlServer::CMySqlServer()
{
    //初始化数据库连接
    mpcon = mysql_init((MYSQL*)0);
    if(mpcon == NULL)
    {
        cout<<"mysql init error"<<endl;
        //exit(-1);
        throw "";
    }
    
    if(!mysql_real_connect(mpcon, "127.0.0.1", "root", 
        "123456", NULL, 5000, NULL, 0))
    {
        cout<<"mysql connect error"<<endl;
        //exit(-1);
        throw "";
    }
    
    if(mysql_select_db(mpcon, "Chat"))
    {
        cout<<"mysql select db error"<<endl;
        //exit(-1);
        throw "";
    }
    
    cout<<"mysql server init success!"<<endl;
}
CMySqlServer::~CMySqlServer()
{
    if(mpres != NULL)
        mysql_free_result(mpres);  
    if(mpcon != NULL)
        mysql_close(mpcon);
}

///////////////////////////////////////////////
CMySqlServer gMySqlServer;