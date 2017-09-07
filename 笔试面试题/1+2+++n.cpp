#include <iostream>
using namespace std;

// 1+2+3----+n

//µÝ¹é
int Add1(int n)
{
	return n<=0 ? 0 : n + Add1(n - 1);
 } 
 
 //·ÇµÝ¹é
int Add2(int n)
{
	int sum = 0; 
	for(int i = 1;i<=n;i++)
		sum += i;
	return sum;
} 

int main()
{
	cout<<Add1(19)<<endl;
	cout<<Add2(19)<<endl;
	cout<<Add2(50000)<<endl;
	cout<<Add1(50000)<<endl;//Õ»Òç³ö 
}

