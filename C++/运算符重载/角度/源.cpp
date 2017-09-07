#include <iostream>
#include <string>
using namespace std;

class Angle
{

public:
	int d, f, m;
	Angle(){ d = f = m = 0; };
	Angle(int a, int b, int c)
	{
		d = a, f = b, m = c;
	}
	Angle(int a)
	{
		d = a / 3600;
		f = (a - d * 3600) / 60;
		m = (a - d * 3600 - f * 60);
	}
	friend  Angle operator+(Angle &c, Angle &b)
	{
		Angle a;
		a.d = c.d + b.d;
		a.f = c.f + b.f;
		a.m = c.m + b.m;
		a.f += a.m / 60;
		a.m %= 60;
		a.d += a.f / 60;
		a.f %= 60;
		a.d %= 60;
		return a;
	}
	friend  Angle operator-(Angle &c, Angle &b)
	{
		Angle a;
		a.d = c.d - b.d;
		a.f = c.f - b.f;
		a.m = c.m - b.m;
		if (a.m < 0)
		{
			a.m += 60;
			a.f--;
		}
		if (a.f < 0)
		{
			a.f += 60;
			a.d--;
		}
		if (a.d < 0)
			a.d += 60;
		return a;
	}
	operator int()
	{
		return d * 3600 + f * 60 + m;
	}
	void display()
	{
		cout << this->d << "度" << f << "分" << m << "秒\n";
	}
};

int main()
{
	int i = 4201;
	Angle a1 = Angle(19, 30, 22);
	Angle a2 = Angle(11, 34, 39);
	Angle a3 = a1 + a2;
	a3.display();
	a3 = a1 - a2;
	a3.display();
	a3 = a1 + i;
	a3.display();
	int j = (int)a3;  //注意显式类型转换与隐式类型转换的区别
	cout << j << endl;

	system("pause");
	return 0;
}
