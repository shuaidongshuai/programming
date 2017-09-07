#include<iostream>
#include <cstdlib>
using namespace std;

#define max(a,b) ((((a)-(b))&(1<<31))?(b):(a)) 

#define max2(a,b) (((abs((a)-(b)))==((a)-(b)))?(a):(b))

int main()
{
	cout<<max(6,7)<<endl;
	cout<<max2(6,7)<<endl;
}
