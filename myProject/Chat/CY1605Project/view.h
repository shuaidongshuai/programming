#ifndef VIEW_H
#define VIEW_H
#include <json/json.h>
#include <string>
using namespace std;

class View
{
public:
    virtual void process(Json::Value root)=0;
    virtual string response()=0;
};

#endif