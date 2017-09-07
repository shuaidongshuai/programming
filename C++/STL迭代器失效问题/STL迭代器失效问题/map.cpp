#include <iostream>
#include <map>
using namespace std;

//É¾³ý 3->3			5->3
void test(map<int, int> &m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end();)
	{
		if (it->second == 3)
			m.erase(it++);
		else
			it++;
	}
}
//Ôö¼Ó
void test2(map<int, int> &m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end();++it)
	{
		if (it->second == 1)
			m[3] = 30;
	}
}
void print(map<int, int> &m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end();++it)
		cout << it->first << " => " << it->second << endl;
}

int main()
{
	map<int,int> m;
	for (int i = 4; i >= 0; --i)
		m[i] = i;
	m[5] = 3;

	test(m);
	print(m);
	cout << "-------------" << endl;
	test2(m);
	print(m);
	system("pause");
	return 0;
}