#include<iostream>
using namespace std;

enum word{ hello, now };
class Frog;
//王子类
class Prince
{
public:
	virtual void currentState(Frog*, enum word){}
};
//青蛙类
class Frog
{
	Prince* prince = NULL;
public:
	void setState(Prince *prince)
	{
		if (this->prince != NULL)
			delete this->prince;
		this->prince = prince;
		你好王子();
	}
	void 你好王子()
	{
		cout << "你好啊王子" << endl;
		prince->currentState(this, hello);
		现在几点钟了();
	}
	void 现在几点钟了()
	{
		cout << "现在几点钟了？" << endl;
		prince->currentState(this, now);
	}
};
//王子的状态
//晚上
class noon :public Prince
{
	void currentState(Frog* frog, enum word w)
	{
		switch (w)
		{
		case hello: cout << "小青蛙又看见你了" << endl; break;
		case now: cout << "现在是晚上" << endl;
		}
	}
};
//早上
class morning :public Prince
{
	void currentState(Frog* frog, enum word w)
	{
		switch (w)
		{
		case hello:cout << "小青蛙你好啊" << endl; break;
		case now:cout << "现在是上午" << endl; frog->setState(new noon);
		}
	}
};


int main2()
{
 	Frog().setState(new morning);
	

	system("pause");
	return 0;
}