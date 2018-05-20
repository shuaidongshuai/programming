#include <iostream>
using namespace std;
int main()
{
	int m, n, temp;
	cin >> m >> n;
	while(n){
		temp = n;
		n = m % n;
		m = temp;
	}
	cout << m << endl;
}
