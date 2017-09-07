#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <fstream>
#include <iterator>
#include <functional>
using namespace std;

int test7()
{
	int n;
	string str;
	multiset<int, greater<int>> s;
	cin >> n;
	while (n--)
	{
		cin >> str;
		int i = atoi(str.c_str());
		s.insert(i);
	}
	int a = 0, b = 0, a2 = 0, b2 = 0;
	multiset<int, greater<int>>::iterator it = s.begin();
	//copy(s.begin(), s.end(), ostream_iterator< int >(cout, " "));
	while (it != s.end())
	{
		if (a2 == 0)
		{
			a2 = *it++;
			a += a2;
		}
		if (b2 == 0)
		{
			b2 = *it++;
			b += b2;
		}
		--a2;
		--b2;
	}
	cout << endl;
	cout << max(a, b) << endl;
	return 0;
}
/*
5
3072 3072 7168 3072 1024
*/
#define N 10000000
using namespace std;
int prime[N];
int arr[N];
int test8()
{
	int i, j, n, max;
	cin >> max >> n;
	for (int i = 0; i<max; i++)
		prime[i] = true;
	for (i = 2; i <= sqrt((double)max); i++)
	{
		if (prime[i])
			for (j = i + i; j<max; j += i)
				prime[j] = false;
	}
	j = 0;
	for (i = 2; i<500; i++)
		if (prime[i])
			arr[j++] = i;
	int x = 0, sum = 0;
	while (x <= j - 1)
	{
		if (arr[i] + arr[j - 1] == n)
		{
			sum += 1;
			i++;
		}
		else if (arr[i] + arr[j - 1] < n)
			i++;
		else
			j--;
	}

	cout << sum << endl;

	return 0;
}