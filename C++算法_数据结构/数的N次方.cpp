#include <iostream>
#include <stdexcept>
using namespace std;
 /**		只考虑指数为整数
 * 1.全面考察指数的正负、底数是否为零等情况。
 * 2.写出指数的二进制表达，例如13表达为二进制1101。
 * 3.举例:10^1101 = 10^0001*10^0100*10^1000。
 * 4.通过&1和>>1来逐位读取1101，为1时将该位代表的乘数累乘到最终结果。
 */
double Power(double base, int n){
	double res = 1;
	int exp = n;
	if(n > 0)
		exp = n;
	else if (n < 0){
		if(base == 0)
			throw runtime_error("分母不能为0");
		exp = -n;
	}
	else{
		if(base == 0)
			throw runtime_error("0的0次方没有意义");
		return 1;
	}
	while(exp){
		if(exp & 1 == 1)
			res *= base;
		exp >>= 1;// 右移一位
		base *= base;// 翻倍
	}
	return n >=0 ? res : (1 / res);
}

int main(){
	try{
		cout<<Power(2,3)<<endl;
		cout<<Power(2,-2)<<endl;
		cout<<Power(0,0)<<endl;
		cout<<Power(0,-1)<<endl;
	}catch(runtime_error &e){
		cout<<e.what()<<endl;
	}
	
}
/*
	8
	0.25
	0的0次方没有意义
*/