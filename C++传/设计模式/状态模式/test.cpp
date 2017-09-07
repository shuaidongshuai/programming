#include <iostream>
using namespace std;
class Fro
{
public:
	enum e{ hello, nice };
	Fro()
	{
		cout << typeid(hello).name() << endl;
		dong2(hello);
		//dong1(hello);//不知道为什么报错。。可能是类中的enum不能传出去吧。在类中调用就是不好使
	}
	void dong2(enum e w)
	{
		cout << w << endl;
	}
};
void dong1(enum Fro::e w)
{
	cout << w << endl;
	cout << Fro::nice << endl;
}
int main()
{
	Fro* fro = new Fro;
	enum Fro::e w = Fro::hello;
	dong1(w);

	system("pause");
	return 0;
}