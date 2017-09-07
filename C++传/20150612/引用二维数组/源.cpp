#include<iostream>
#include<tuple>
using namespace std;


void main()
{
	int a[2][2] = {1, 2, 3, 4};
	int (&aa)[2][2](a);
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			cout << aa[i][j];
		}
		cout << endl;
	}





	cin.get();
}