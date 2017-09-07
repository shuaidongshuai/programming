#include <iostream>
#include <cmath> 
using namespace std;

//不用判断语句 找到两个数中大的那个 

// 就算不让用abs这个函数，自己也可以写一个
int my_abs(int a)
{
	return (a ^ (a >> 31)) - (a >> 31);
	/*
	如果a是整数 a >> 31肯定等于0 异或后 还是原来的数  再减去0还是原来的数
	如果a是负数 a >> 31肯定是-1  异或后 相当于给a取反 再减去-1 相当于 +1 那么不就是得到a的负数了么
	*/
}

int main()
{
	int a = 5;
	int b = 20;
	///////////////////第一种方法//////////////////////////
	cout<< ((a + b) + my_abs(a - b)) / 2 <<endl;
	///////////////////第二种方法///////////////////////////
	int res[2] = {a,b};
	//int index = (a - b) >> (sizeof(int) * 8 - 1) & 1;
	//int index = unsigned(a - b) >> (sizeof(int) * 8 - 1); //两种写法都可以，下面这个就是把负数变为正数，右移的时候最高位补0，上面是补1
	int index = unsigned(a - b) >> 31;//如果不考虑跨平台的话
	cout<<res[index]<<endl;
	//////////////////第二种方法还能求最小值///////////////////////////
	cout<<res[1 - index]<<endl;
}
