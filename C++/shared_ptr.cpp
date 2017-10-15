#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

void test1(){
	shared_ptr<string> pNico(new string("nico"));
	shared_ptr<string> pJutta(new string("jutta"),
		[](string *p) {
		cout << "delete " << *p << endl;
		delete p;
	}
	);

	(*pNico)[0] = 'N';
	pJutta->replace(0, 1, "J");

	vector<shared_ptr<string>> whoMadeCoffee;
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pNico);
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pNico);

	for (auto ptr : whoMadeCoffee)
		cout << *ptr << " ";
	cout << endl;

	*pNico = "Nicolai";
	for (auto ptr : whoMadeCoffee)
		cout << *ptr << " ";
	cout << endl;
	
	cout << "use_count: " << whoMadeCoffee[0].use_count() << endl;
}
/*
Jutta Nico Jutta Nico
Jutta Nicolai Jutta Nicolai
use_count: 3
delete Jutta
*/
void test2(){
	int *p = new int(6);
	shared_ptr<int> sp(p);
	cout<<p<<endl;
	cout<<&(*sp)<<endl;
	cout<<sp.use_count()<<endl;
	shared_ptr<int> p2 = sp;
	cout<<sp.use_count()<<endl;
}
/*
0xa114e0
0xa114e0
1
2
*/
class A{
public:
	A(){cout<<"构造"<<endl;}
	~A(){cout<<"xigou"<<endl;}
};
void test3(){
//	shared_ptr<A[]> sp(new A[2]); 	shared_ptr"不能指向数组" 默认析构只有delete 
	shared_ptr<A> sp(new A[2],	//但是可以指向数组的首地址 
	[](A *a){
		cout<<"自定义析构函数"<<endl; 
		delete[] a;		//注意：如果指向的是数组，必须自定义析构函数，默认调用的是 delete 
	}
	);
}
int main(){
	//test1();
	test3();
}

