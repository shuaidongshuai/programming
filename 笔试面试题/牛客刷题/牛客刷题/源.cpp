/*
可能有多组测试数据，对于每组数据，将给出的N个数从小到大进行排序，输出排序后的结果，每个数占一行。
输入例子:
3
11111111111111111111111111111
2222222222222222222222222222222222
33333333

输出例子:
33333333
11111111111111111111111111111
2222222222222222222222222222222222
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

bool comp(string a, string b)
{
	if (a.length() < b.length())
		return true;//返回true说明第一个将要排在第二个前面
	else if (a.length() > b.length())
		return false;
	//说明一样长
	return a < b;//string可以直接比大小，按字典序进行比较，a<b 为真返回true
}

int main()
{
	int n;
	while (cin >> n)
	{
		vector<string> v(n);
		for (int i = 0; i < n; ++i)
			cin >> v[i];
		sort(v.begin(), v.end(),comp);
		//copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
		for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
			cout << *it << endl;
	}
	return 0;
}