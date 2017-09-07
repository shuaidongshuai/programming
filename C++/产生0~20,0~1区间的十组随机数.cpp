#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
	double d;
	int i,n; 
	srand(time(0));
	for(i=0;i<10;i++)
	{
		n=rand()%20;				//产生0~20之间的随机整数 
		d=rand()/(double)RAND_MAX;	//产生0`1之间的小数 
		cout<<n<<"\t"<<d<<endl;
	}
	return 0;
 } 
