#include "controller.h"
#include "loginview.h"
#include "json/json.h"
#include "public.h"

Controller gController;

Controller::Controller()
{
    _viewMap.insert(make_pair("login", new LoginView()));
    
    cout<<"controller init success!"<<endl;
}

void Controller::process(string json)
{
    Json::Reader reader;
    Json::Value root;
    
    if(0 == reader.parse(json.c_str(), root))
    {
        cerr<<"json format invalid:"<<json<<endl;
        return;
    }
    
    int msgtype = root["msgtype"].asInt();
    switch(msgtype)
    {
        case MSG_TYPE_LOGIN:
        {
            map<string, View*>::iterator it = _viewMap.find("login");
            it->second->process(root);
            it->second->response();
        }
    }
}