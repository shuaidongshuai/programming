#ifndef __SINGLE_H__
#define __SINGLE_H__
template<typename T>
class Singleton1
{
public:
	static T *getInstance()
	{
		static T *instance = new T;
		return instance;
	}
	virtual ~Singleton1(){}
};
#endif