#include<iostream>
#include<vector>
using namespace std;

int main4()
{
	vector<int> table(4);
	for (int i = 0; i < 4; ++i)
		table[i] = i;

	vector<int> n1(table.begin(), table.end());

	//cout << *table.begin() << "   " << *table.end();
	cout << table.front() << "   " << table.back() << endl;
	cout << n1.front() << "   " << n1.back() << endl;


	system("pause");
	return 0;
}