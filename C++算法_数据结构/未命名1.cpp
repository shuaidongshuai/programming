#include <iostream> 
#include <algorithm>
#include <cstring>
using namespace std;
struct s
{
	int x: 1;
    char y: 1;
    
    char z: 1;
};
int main()
{
	cout<<sizeof(s)<<endl;
}

