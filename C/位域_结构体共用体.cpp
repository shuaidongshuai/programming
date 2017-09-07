#include <iostream>
using namespace std;
struct dong
{
	unsigned a1:1;
	unsigned a2:2;
	unsigned a3:3;
	int b;
};
int main()
{
	struct dong d;
	d.a1 = 15;// 0xf   bin: 1111
	d.a2 = 15;
	d.a3 = 15;
	d.b = 15;
	cout<<d.a1<<endl;//bin: 1 
	cout<<d.a2<<endl;//		11 
	cout<<d.a3<<endl;//		111
	cout<<d.b<<endl;//		1111
}

/*
该种形式出现于结构体或共用体的定义中，是位域定义的标准形式。
其使用方式为
struct name
{
    type var_name : n;

};
含义为，在结构体name汇总，成员变量var_name占用空间为n位。
n为正整数，其值必须小于type类型占用的位数。比如type如果是int，占4字节32位，那么n必须是1~31之间的整数。
对于位域类型的成员，在赋值时如果实际值超过n位所能表达的范围，那么超出部分将会被截掉，只保存低位值。
如int var:4,本身只有4位的空间，如果赋值var = 20, 由于20的二进制值为10100，实际为五位，这时var实际被赋值的就是低四位，0100，即4。

由于C语言中的地址是针对字节计算的，所以位域类型的成员变量不支持取地址操作，即对于变量v, 如果存在位域成员变量var，那么&a.var是非法的，编译会出错。
*/
