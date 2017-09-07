#include <iostream>
#include <string>
using namespace std;

class Complex
{
public:
	double real, image;
	Complex():real(0), image(0){}
	Complex(double r, double i = 0) :real(r), image(i){}
	Complex(int r) :real(r), image(0){}
	Complex operator + (const Complex &c)
	{
		return Complex(real + c.real, image + c.image);
	}
	Complex operator - (const Complex &c)
	{
		return Complex(real - c.real, image - c.image);
	}
	Complex operator * (const Complex &c)
	{
		return Complex(real * c.real, image * c.image);
	}
	Complex operator / (const Complex &c)
	{
		return Complex(real / c.real, image / c.image);
	}
	friend Complex operator -(const Complex &c)
	{
		return Complex(-c.real, -c.image);
	}
	template<typename T>
	operator T()
	{
		return sqrt(real*real + image*image);
	}
	bool operator ==(const Complex &c)
	{
		return real == c.real ? image == c.image : false;
	}
	bool operator !=(const Complex &c)
	{
		return !(*this == c);
	}
	bool equals(const Complex &c)
	{
		return *this == c;
	}
	void ToString()
	{
		if (image && real)
		{
			if (image < 0)
				cout << real << image << "i" << endl;
			else
				cout << real << "+" << image << "i" << endl;
		}
		else if (image)
			cout << image << "i" << endl;
		else
			cout << real << endl;
	}
	
};

int main()
{
	int i = 1;
	Complex c1 = Complex(2, 2);
	Complex c2 = -c1;
	Complex c3 = c1 + c2;
	c3.ToString();

	c3 = c1 - c2;
	c3.ToString();

	c3 = c1*c2;
	c3.ToString();

	c3 = c1 / c2;
	c3.ToString();

	c3 = c1 - i;
	c3.ToString();

	double j = c3;//ÏÔÊ½×ª»»
	cout << j << endl;
	
	cout << (c2 == c3) << endl;

	system("pause");
	return 0;
}