#include <iostream>
#include <map>
#include <string>
using namespace std;
/*
隔一个删除一个map中的元素(主要考察迭代器的失效问题) 
*/ 
void print(map<int, string> &m)
{
	for(map<int, string>::iterator it = m.begin();it != m.end();++it)
	{
		cout<<it->first<<":"<<it->second<<endl;
	}
	cout << "---------------------" << endl;
}
int main()
{
	map<int,string> IntMap;
	for(int i = 0;i<5;++i)
	{
		IntMap[i] = i + '0';
	}
	print(IntMap);
	for(map<int,string>::iterator it = IntMap.begin();it != IntMap.end();/*不能再自增了*/)
	{
		if(it->second == "3")
		{
			IntMap.erase(it++);
		}
		else
			it++;
	}
	print(IntMap);
}
