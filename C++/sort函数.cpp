#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>//sort 
#include <functional>//greater
using namespace std;
//sort()可以传地址，也可以传迭代器
void stlTest()
{
	vector<int> v;
	srand(time(0));
	for (int i = 0; i<6; ++i)
		v.push_back(rand() % 100);
	sort(v.begin(), v.end());//默认从小到大
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;

	sort(v.begin(), v.end(), greater<int>());//从大到小
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;
}
void test()
{
	int arr[6];
	for (int i = 0; i<6; ++i)
		arr[i] = rand() % 100;
	sort(arr, arr + 6);//传地址进出也可以
	for (int i = 0; i < 6; ++i)
		cout << arr[i] << " ";
	cout << endl;

	sort(arr, arr + 6,greater<int>());
	for (int i = 0; i < 6; ++i)
		cout << arr[i] << " ";
	cout << endl;
}
int main()
{
	stlTest();
	test();
}

