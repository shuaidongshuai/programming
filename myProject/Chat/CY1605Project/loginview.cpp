#include "loginview.h"
#include <json/json.h>
#include <stdio.h>
#include <string.h>
#include "public.h"


extern CMySqlServer gMySqlServer;

////////////////////////////////////////////////////////
bool LoginModel::checkUserAuth(string name, string pwd)
{
    char sql[1024]={0};
    sprintf(sql, "select * from user;");
    
    /*
    先从memcached里面查询，ok返回结果
    fail，从数据库查询
    */
    
    //发送sql查询语句，查询表的内容
    if(mysql_real_query(gMySqlServer.mpcon,sql,strlen(sql)))
    {
        return false;
    }
    
    //从连接处获取select查询的结果 =》  二维表
    gMySqlServer.mpres = mysql_store_result(gMySqlServer.mpcon);
    //循环从二维表中取出一个个记录,分别访问它的每一个字段
    while(gMySqlServer.mrow = mysql_fetch_row(gMySqlServer.mpres))
    {
        if(strcmp(name.c_str(), gMySqlServer.mrow[0]) == 0)
        {
            //把该用户的信息缓存到memcached当中
            
            if(strcmp(pwd.c_str(), gMySqlServer.mrow[1]) == 0)
            {
                return true;
            }
            
        }
    }
    return false;
}


/////////////////////////////////////////////////////////
void LoginView::process(Json::Value root)
{
    _name = root["name"].asString();
    _pwd = root["pwd"].asString();
    
    //访问对应的LoginModel模块进行用户名，密码验证
    if(_loginModel.checkUserAuth(_name, _pwd))
        _bloginState = true;
    else
        _bloginState = false;
}
string LoginView::response()
{
    Json::Value response;
    response["msgtype"] = MSG_TYPE_ACK;
    if(_bloginState)
    {
        response["reason"] = "ok";
    }
    else
    {
        response["reason"] = "name or pwd is invalid!";
    }
    return response.toStyledString();
}