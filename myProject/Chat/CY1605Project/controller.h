#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <map>
#include <string>
using namespace std;
#include "view.h"

class Controller
{
public:
    //注册所有现存的视图
    Controller();
    void process(string json);
private:
    map<string, View*> _viewMap;
};

#endif