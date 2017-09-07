#ifndef LOGINVIEW_H
#define LOGINVIEW_H
#include "mysqlserver.h"
#include "view.h"
#include <string>
using namespace std;


class LoginModel 
{
public:
    bool checkUserAuth(string name, string pwd);
};

class LoginView : public View
{
public:
    void process(Json::Value root);
    string response();
private:
    string _name;
    string _pwd;
    LoginModel _loginModel;
    bool _bloginState;
};

#endif