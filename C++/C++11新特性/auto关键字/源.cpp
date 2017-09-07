#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<int> v;
	for (int i = 0; i < 5; ++i)
	{
		v.push_back(i);
	}
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	getchar();
}