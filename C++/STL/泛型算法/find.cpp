#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

void myFind()
{
	int search_value = 12;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };
	int len = sizeof(ia) / sizeof(ia[0]);
	int *presult = find(ia, ia + len, search_value);
	cout << "The value " << search_value << (presult == ia + len ? " is not present" : " is present") << endl;
}

void vectorFind()
{
	int search_value = 12;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };
	vector<int> vec(ia, ia + 6);
	vector<int>::iterator presult;
	presult = find(vec.begin(), vec.end(), search_value);
	cout << "The value " << search_value
		<< (presult == vec.end()
		? " is not present" : " is present")
		<< endl;
}

void listFind()
{
	int search_value = 12;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };
	list<int> ilist(ia, ia + 6);
	list<int>::iterator presult;
	presult = find(ilist.begin(), ilist.end(), search_value);
	cout << "The value " << search_value
		<< (presult == ilist.end()
		? " is not present" : " is present")
		<< endl;
}