#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

void myCopy()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	//左移1位
	int len = sizeof(arr) / sizeof(arr[0]);
	copy(arr + 1, arr + len,arr);//包含头，不包含尾，所以是 + len 
	for (int i = 0; i < len; ++i)
		cout << arr[i] << " ";
	cout << endl;
}
void myCopy2()
{
	int ia[] = { 0, 1, 1, 3, 5, 8, 13 };
	vector<int> vec(ia, ia + 7);//包含头，不包含尾
	ostream_iterator< int > ofile(cout, " ");
	copy(vec.begin(), vec.end(), ofile);
	cout << endl;
	// 左移 1 位
	copy(ia + 1, ia + 7, ia);
	copy(ia, ia + 7, ofile);
	cout << endl;
	// 左移 2 位
	copy(vec.begin() + 2, vec.end(), vec.begin());
	copy(vec.begin(), vec.end(), ofile); cout << '\n';
}