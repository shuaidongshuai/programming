#include <iostream>
using namespace std;

class Test2{
public:
	Test2()
	{
		cout<<"构造函数"<<endl; 
	}
	void show()
	{
		cout<<"东"<<endl;
	}
	~Test2()
	{
		cout<<"析构函数"<<endl; 
	}
};

int main()
{    
    Test2().show();//这句话执行完。就调用析构函数 
    
    cout<<"★★★★★★★★★★★★★★★★★★★"<<endl;
    /*
	构造函数
	东
	析构函数
	★★★★★★★★★★★★★★★★★★★
	*/ 
    
    return 0;
}
