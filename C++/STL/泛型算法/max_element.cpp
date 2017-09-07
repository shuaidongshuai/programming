#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>
#include <algorithm>
#include <functional>
using namespace std;

void myMax()
{
	int search_value = 12;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };
	int len = sizeof(ia) / sizeof(ia[0]);
	int *presult = max_element(ia, ia + len);
	cout << "The Max " << *presult << endl;
}

void vectorMax()
{
	int search_value = 12;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };
	vector<int> vec(ia, ia + 6);
	vector<int>::iterator presult;
	presult = max_element(vec.begin(), vec.end());
	cout << "The Max " << *presult << endl;
}

void listMax()
{
	int search_value = 12;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };
	list<int> ilist(ia, ia + 6);
	list<int>::iterator presult;
	presult = max_element(ilist.begin(), ilist.end());
	cout << "The Max " << *presult << endl;
}