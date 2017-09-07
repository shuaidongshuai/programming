#include<iostream>
using namespace std;

namespace dong
{
	struct dong
	{
		int i;
		void show()
		{
			cout << i << endl;
		}
		
		int add(int a, int b);
	};
}
int dong::dong::add(int a, int b)
{
	return a + b;
}

void main()
{
	dong::dong run;
	run.i = 100;
	run.show();
	cout << run.add(100, 100) << endl;

	cin.get();
}
