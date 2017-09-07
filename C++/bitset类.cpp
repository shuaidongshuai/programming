#include <iostream>
#include <bitset>
#include <typeinfo>
using namespace std;
/*注意角标都是从0开始*/
int main1()
{
	bitset<100> b;			//初始化全是0 
	cout<<b.test(2)<<endl;  //test( pos ) pos 位是否为1
	b.set(2);				//set( pos ) 将pos 位置1
	cout<<b<<endl;
	
	cout<<b.any()<<endl;	//任意位是否为1
	
	b.set(6);
	cout<<b.count()<<endl;	//值是1 的位的个数
	
	cout<<b.size()<<endl;	//位元素的个数
	
	cout<<b[6]<<" "<<b[7]<<endl;	//[pos] 访问pos 位
	
	b.set();				//将所有位置1
	cout<<b.count()<<endl;
	
	b.reset(2);				//将pos 位置0
	cout<<b.count()<<endl;
	
	b.reset();				//将所有位置0
	cout<<b.count()<<endl;
}

int main()
{
	bitset<10> b(12);		//十进制转化为二进制，再和刚初始化好的10个0  进行 或运算   0000001100
	cout<<b<<endl;
	
	bitset<10> bb;
	bb = 4;					//直接赋值也可以 
	cout<<bb<<endl;
	
	bitset<10> b2(012);		//8进制 0000001010
	cout<<b2<<endl;
	
	bitset<10> b3(0xf);		//0000001111
	cout<<b3<<endl; 
	 
	string s = "111000";
	bitset<10> b4(s);		//0000111000
	cout<<b4<<endl;
	
	string s2 = b4.to_string();//将任意bitset 对象转换成string
	cout<<s2<<endl;
	
	unsigned long a = b.to_ulong();//将任意bitset 对象转换成unsigned long 型的整数表示
	cout<<a<<endl;
	
	bitset<10> b5 = b | b2;
	bitset<10> b6 = b & b2;
	cout<<b5<<endl;
	cout<<b6<<endl;
	
	cout<<typeid(b5).name()<<endl;
}
