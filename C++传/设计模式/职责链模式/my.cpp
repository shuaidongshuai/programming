#include <iostream>
#include <string>
using namespace std;

class god
{
public:
	virtual void deal(int money)
	{
		if (money < 5000)
		{
			cout << "上帝：拿去买个媳妇" << endl << endl;
			return;
		}
		cout << "上帝都帮不了你" << endl;
	}
};
class grandfather :public god
{
public:
	void deal(int money)
	{
		if (money < 3000)
		{
			cout << "爷爷：拿去买个手机" << endl << endl;
			return;
		}
		cout << "爷爷帮不了你，你去问上帝要吧！" << endl;
		god::deal(money);
	}
};
class father :public grandfather
{
public:
	void deal(int money)
	{
		if (money < 2000)
		{
			cout << "爸爸：拿去买水果" << endl << endl;
		}
		cout << "爸爸帮不了你，你去问爷爷要吧！" << endl;
		grandfather::deal(money);
	}
};
class mother :public grandfather
{
public:
	void deal(int money)
	{
		if (money < 1000)
		{
			cout << "妈妈：拿去买糖" << endl << endl;
		}
		cout << "妈妈帮不了你，你去问爷爷要吧！" << endl;
		grandfather::deal(money);
	}
};
int main()
{
	mother().deal(4000);

	father().deal(6000);

	system("pause");
	return 0;
}