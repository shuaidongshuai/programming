#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <vld.h>
using namespace std;

/*监听者*/
class Listener
{
public:
	string name;
public:
	Listener(string n) :name(n){}
	virtual void handleMessage(int msgid) = 0;//回调函数
};
/*几个注册监听者的用户*/
class Listener1:public Listener
{
public:
	Listener1(string n) :Listener(n){}
	virtual void handleMessage(int msgid)
	{
		/*处理自己感兴趣的事*/
		switch (msgid)
		{
		case 0:cout << name << " recv 0" << endl; break;
		case 1:cout << name << " recv 1" << endl; break;
		default:cout << name << "不感兴趣" << endl;
		}
	}
};
class Listener2 :public Listener
{
public:
	Listener2(string n) :Listener(n){}
	virtual void handleMessage(int msgid)
	{
		/*处理自己感兴趣的事*/
		switch (msgid)
		{
		case 0:cout << name << " recv 0" << endl; break;
		case 2:cout << name << " recv 2" << endl; break;
		default:cout << name << "不感兴趣" << endl;
		}
	}
};
class Listener3 :public Listener
{
public:
	Listener3(string n) :Listener(n){}
	virtual void handleMessage(int msgid)
	{
		/*处理自己感兴趣的事*/
		switch (msgid)
		{
		case 1:cout << name << " recv 1" << endl; break;
		case 2:cout << name << " recv 2" << endl; break;
		default:cout << name << "不感兴趣" << endl;
		}
	}
};
/*观察者*/
class Observer
{
public:
	/*为某一个监听者注册一个消息*/
	void registerMsg(weak_ptr<Listener> listener, int msgid)
	{
		map<int, vector<weak_ptr<Listener>>>::iterator it = obserMap.find(msgid);//查看消息是否已经被监听
		vector<weak_ptr<Listener>> v;
		if (it == obserMap.end())//没有被监听
		{
			v.push_back(listener);
		}
		else//已经监听了这个消息，那么只需要把这个用户加入向量中
		{
			/*还需要判断一下有没有重复注册*/
			/*也加上了线程安全*/
			v = it->second;
			for (vector<weak_ptr<Listener>>::iterator it = v.begin(); it != v.end(); ++it)
			{
				shared_ptr<Listener> p = (*it).lock();
				if (!p)
					return;
				if (p == (shared_ptr<Listener>)listener)/*如果找到这个用户已经注册*/
					return;
			}
			v.push_back(listener);
		}
		obserMap[msgid] = v;
	}
	/*当观察到消息，就分发出去*/
	void dispatchMsg(int msgid)
	{
		map<int, vector<weak_ptr<Listener>>>::iterator it = obserMap.find(msgid);
		if (it != obserMap.end())
		{
			for (vector<weak_ptr<Listener>>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				/*线程安全*/
				shared_ptr<Listener> p = (*it2).lock();
				if (p)
				{
					p->handleMessage(msgid);
				}
			}
		}
	}
	map<int, vector<weak_ptr<Listener>>> obserMap;
};
/*
1.产生对象的时候用，强智能指针shared_ptr
2.把指针泄露给别的线程时用，弱智能指针weak_ptr
3.在别的线程想使用这个智能指针，需要把弱智能指针转化为强智能指针
4.调用.lock()返回为空，说明这个共享对象在别的线程中已经呗析构了
只解决了C++共享对象的线程安全（其他线程安全问题没有解决）
*/
int main()
{
	/*线程1*/
	/*创建三个用户*/
	shared_ptr<Listener> l1(new Listener1("Listener1"));
	shared_ptr<Listener> l2(new Listener2("Listener2"));
	shared_ptr<Listener> l3(new Listener3("Listener3"));
	/*一个监听者*/
	Observer obser;

	/*为用户注册消息*/
	obser.registerMsg(l1, 0);
	obser.registerMsg(l1, 1);
	obser.registerMsg(l2, 0);
	obser.registerMsg(l2, 2);
	obser.registerMsg(l3, 1);
	obser.registerMsg(l3, 2);
	
	/*线程2*/
	int msgid;
	while (cin >> msgid)
	{
		obser.dispatchMsg(msgid);
	}
	return 0;
}