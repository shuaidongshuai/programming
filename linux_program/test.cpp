#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int a = 20;
	cout<<a<<endl;
	vector<int> v(2,5);
	for(vector<int>::iterator it = v.begin();it != v.end();++it)
	{
		cout<<*it<<endl;
	}
}
