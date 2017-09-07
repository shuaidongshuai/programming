#include <iostream>
#include <iomanip>
#include <cstring>
#include <bitset>
using namespace std;

int main()
{
	int a = 7;
	cout << bitset<8>(a) << endl;//用别人的类，需要加头文件

	char buf[32];
	_itoa_s(a, buf, 2);
	cout << buf << endl;
	
	/*	两种转换2进制的方法
	00000111
	111
	*/

	system("pause");
	return 0;
}
int main4()
{
	int i, j, k, l;
	cout << "Input i(oct), j(hex), k(hex), l(dec) :" << endl;
	cin >> oct >> i; //输入为八进制数
	cin >> hex >> j; //输入为十六进制数
	cin >> k; //输入仍为十六进制数		用了hex之后，就默认了hex
	cin >> dec >> l; //输入为十进制数
	cout << "输出" << endl;
	cout << "i = " << i << endl;
	cout << "j = " << j << endl;
	cout << "k = " << l << endl;
	cout << "l = " << k << endl;
	/*
	Input i(oct), j(hex), k(hex), l(dec) :
	20 20 20 20										// 0  和 0x 可以省略
	输出
	i = 16		//  8进制 20  == 10进制 16
	j = 32		// 16进制 20  == 10进制 32
	k = 20		
	l = 32		// 16进制 20  == 10进制 32

	Input i(oct), j(hex), k(hex), l(dec) :
	020 0x20 0x20 20								
	输出
	i = 16
	j = 32
	k = 20
	l = 32
	*/
	
	/*
几点说明：
					
使用不带.h的头文件<iostream>时，必须在cin中指明数制，否则从键盘输入时，不认八进制和十六进制数开头的0和0x标志。指明后可省略0和0x标志。

进制控制只适用于整型变量，不适用于实型和字符型变量。

输入数据的格式、个数和类型必须与cin中的变量一一对应，否则不仅使输入数据错误，而且影响后面其他数据的正确输入。

在cin或cout中指明数制后，该数制将一直有效，直到重新指明使用其他数制。
	*/
	system("pause");
	return 0;
}

int main3()
{
	cout.width(8);
	cout.fill('*');//填充
	cout.setf(ios::showbase);
	cout << hex << 20 << endl;

	cout.width(8);
	cout.fill('*');//填充
	cout.setf(ios::showbase);
	cout.setf(ios::internal);// internal 内部的;
	cout << hex << 20 << endl;

	//使用控制符		效果和上面一样
	cout << setw(8) << setfill('*') << setiosflags(ios::showbase) << setiosflags(ios::internal) << hex << 20 << endl;

	//一般输出16 进制
	cout << "十六进制  " << hex << 20 << endl;
	cout << "八进制    " << oct << 20 << endl;

	/*
	setiosflags的参数是该流的格式标志值，这个值由如下位掩码(ios枚举器)指定，并可用位或OR(|)运算符进行组合：
    ios::skipws  在输人中跳过空白。    
    ios::left  左对齐值，用填充字符填充右边。
    ios::right  右对齐值；用填充字符填充左边(缺省对齐方式)。
    ios::internal  在指定任何引导标记或基之后增加填充字符。
    ios::dec  以基10(十进制)格式化数值(缺省进制)。
    ios::oct  以基8(八进制)格式化数值。
    ios::hex  以基16(十六进制)格式化数值。
    ios::showbase  以C++编译器能读的格式显示数值常量。
    ios::showpoint  对浮点数值显示小数点和尾部的0。
    ios::uppercase  对于十六进制数值显示大写字母A到F，对于科学格式显示大写字母E。
    ios::showpos  对于正数显示正号(+)。
    ios::scientific  以科学格式显示浮点数值。
    ios::fixed  以定点格式显示浮点数值。
    ios::unitbuf  导致在每次插入之后ostream::osfx刷新该流。缺省地，cerr是缓冲的单元。
    ios::stdio  导致在每次插入之后ostream::osfx刷新该流的stdout和stderr。
	*/

	system("pause");
	return 0;
}
int main2()
{
	cout.width(8);
	cout.fill('*');//填充
	cout << "陈明东";

	cout.width(2);
	cout.fill('#');
	cout <<""<< endl;

	system("pause");
	return 0;
}
int main1()
{
	cout << "chen" << endl;
	cout.put('m').put('i').put('n').put('g') << endl;

	char* p = "dong";
	cout.write(p, strlen(p)) << endl;
	cout.write(p, strlen(p) - 1) << endl;
	cout.write(p, strlen(p) + 4) << endl;

	system("pause");
	return 0;
}