#include<iostream>
using namespace std;

int swap(int &a,int &b)
{
	a ^= b;			// 11 ^ 10 = 01
	b ^= a;			// 10 ^ 01 = 11    b 
	a ^= b;			// 01 ^ 11 = 10    a
}

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	for(int i = 0;i<4;++i)
		swap(a[i],a[8-i]);
	for(int i = 0;i<9;++i)
		cout<<a[i]<<" ";
}

/*
100 ^ 010 = 110	 
010 ^ 110 = 100
*/
