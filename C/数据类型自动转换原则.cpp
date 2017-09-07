#include <iostream>
using namespace std;	
//			short,char								    	  float			上面都是无条件转化为下面，比较的时候直接转化为下面类型比较 
//				∨												∨ 
//默认转化     int   ->    long     ->    unsigned     ->     double     	 下面按箭头方向，是默认类型转化，需要的时候才转 

void test1()
{
	unsigned int a = 1;
	char b = -1;
	a>b?cout<<"a>b"<<endl:cout<<"b>=a"<<endl;		//		b>=a			char  ->  unsigned  ||  int  ->  unsigned
} 
void test2()
{
	unsigned short a = 1;
	char b = -1;
	a>b?cout<<"a>b"<<endl:cout<<"b>=a"<<endl;		//		a>b				char  ->   int  || short   ->   int  
}
void test3()
{
	unsigned int a=20;
    signed int b=-130;
    a>b?cout<<"a>b"<<endl:cout<<"b>=a"<<endl;		//		b>=a			
}
void test4()
{
	
	unsigned int a=20;
 	signed int b=-130;
 	std::cout<<a+b<<std::endl;
//结果输出为4294967186，同样的道理，在运算之前，a＝20，b被转化为4294967166，所以a＋b＝4294967186
//减法和乘法的运算结果类似。

//如果作为signed int型数据的c=-130，b与立即数之间操作时不影响b的类型，运算结果仍然为signed int型：
	signed int c = -130;
	std::cout<<c+30<<std::endl;
//输出为-100。				
//而对于浮点数来说，浮点数（float，double）实际上都是有符号数，
//unsigned 和signed前缀不能加在float和double之上，当然就不存在有符号数根无符号数之间转化的问题了。	

//当表达式中存在符号类型和无符号类型时 
//所有的操作数都自动转换为无符号类型 
}
void test5()
{
	//据说是微软面试题：
	unsigned int i=3;
	cout<<i * -1<<endl;						//		4294967293
	cout<<hex<<i*-1<<endl;					//		fffffffd
	cout<<i - 4<<endl;						//		ffffffff
	
	cout<< -1*i + 2 <<endl; 				//		ffffffff
} 
int main()
{
	unsigned int a = 1;
	char b = -1;
	cout<<a<<endl;
	cout<<(unsigned int)b<<endl;
	cout<<(int)b<<endl;
	cout<<"--------------------------"<<endl;
	test1();
	cout<<"--------------------------"<<endl;
	test2();
	cout<<"--------------------------"<<endl;
	test3();
	cout<<"--------------------------"<<endl;
	test4();
	cout<<"--------------------------"<<endl;
	test5();
}
