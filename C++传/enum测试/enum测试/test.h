#pragma once
#include <iostream>
using namespace std;

typedef enum {
	kCCTouchesAllAtOnce,
	kCCTouchesOneByOne,
} ccTouchesMode;
class test
{
	ccTouchesMode m_eTouchMode;
public:
	test();
	~test();
	int i;
	virtual void setTouchMode(ccTouchesMode mode);
	test getText(test t)
	{
		return t;
	}
};
//class MyClass
//{
//public:
//	MyClass();
//	~MyClass();
//	void show()
//	{
//		test* t = new test;
//		test t2 = t->getText();
//		cout << t2.i << endl;
//	}
//private:
//
//};
