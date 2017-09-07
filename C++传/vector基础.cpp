#include <iostream>
#include <vector>
using namespace std; 

void show(vector<int> &v)
{
	for(int i = 0;i<v.size();i++)
	{
		cout<<v[i]<<"   ";
	}
	cout<<endl;
}

int main()
{
	vector<int> v1(20);	//初始化为20个0 
	show(v1);
	
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	show(v1);
	
	vector<int> v2;
	v2 = v1;				//可以直接= 
	show(v2);
	
	cout<<v1.back()<<endl;
	cout<<v1.front()<<endl;
 } 
