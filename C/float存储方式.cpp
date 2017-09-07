#include <iostream>
#include <stdlib.h>
#include <bitset>
using namespace std;

int main()
{
	float a = 10.5;
	int b = (int&)a;
	cout<<a<<endl;					//10.5
	cout<<b<<endl;					//1093140480 							十进制 
	//  10.5  ---二进制>>>   1010.1 
}
//为什么是上面这样的结果呢？

/*
		1010.1 = 1.0101 * 2^3
		
		0		10000010	 			01010000000000000000000
	 符号位		10000010（二进制） 		    	尾数
	  正 		3 + 127 = 130 		  		   .0101
	  
	  最终：0 10000010 01010000000000000000000
*/ 
