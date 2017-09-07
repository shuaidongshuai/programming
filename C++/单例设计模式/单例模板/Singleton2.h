#ifndef __SINGLETON__
#define __SINGLETON__
template <class T>
class Singleton2
{
public:
	static T* getInstance(){ return _instance; }
protected:
	Singleton2(){ _instance = new T; }
	virtual ~Singleton2(){}
	static T* _instance;
};
template <class T> 
T* Singleton2<T>::_instance = NULL;
#endif