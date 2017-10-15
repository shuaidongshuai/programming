#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <typeinfo>
using namespace std;
void func1(char *e)
{ char *p1 = (char *)malloc(100);
 sprintf(p1,"%s'.",e); 
local_log(p1); 
} 
int main(){
	func1("hello");
} 
