#include <iostream>
using namespace std;

/* 这种方法感觉很简单 */
int Fibonacci(int n){
	int f = 0, g = 1;//f当做第0个数，g当做下一个数------1 1 2 3 5
	while(n--){
		g += f;
		f = g - f;
	}
	return f;
}
/*
	有一个题是青蛙只能跳1级台阶和2级台阶，那样几乎就是斐波那契额数列了
	f(n) = f(n - 1) + f(n - 2)----------------------(1)
	f(1) = 1
	f(2) = 2
、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、
	一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级
	求该青蛙跳上一个n级的台阶总共有多少种跳法
、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、
	思路： f(n) 为n级台阶共有N种跳发
	f(n) = f(n - 1) + f(n - 2) + ``` + f(1)---------(1)
	f(n - 1) = f(n - 2) + ``` + f(1)----------------(2)
	f(n) = 2 * f(n - 1)-----------------------------(3)
	f(1) = 1
	f(2) = 2
*/
//递归
int JumpFloorII(int n){
	if(n < 1)
		return -1;
	else if(n == 1)
		return 1;
	else
		return 2 * JumpFloorII(n - 1);
}
//非递归
int JumpFloorII2(int n){
	if(n < 1)
		return -1;
	return 1 << --n;
}

int main(){
	cout<<JumpFloorII(10)<<endl;
	cout<<JumpFloorII2(10)<<endl;
}