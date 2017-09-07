#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

//要求每次调用 pop() push() min() 函数的时间复杂度都是O(1)   min()每次都可以求出栈中的最小元素 

template<class T>
class StackWithMin
{
public:
	void push(T value);
	void pop();
	T min() const;
public:
	int minData;
	stack<T> m_data;
	stack<T> m_min; 			//辅助栈，用来保存最下值 
};

template<class T>
void StackWithMin<T>::push(T value)
{
	m_data.push(value);
	if (m_min.empty() || minData > value)
	{
		minData = value;
		m_min.push(value);
		return;
	}
	m_min.push(minData);
}

template<class T>
void StackWithMin<T>::pop()
{
	m_data.pop();
	m_min.pop();
}

template<class T>
T StackWithMin<T>::min() const
{
	//assert(m_min.size() > 0);  //面试的时候最好写上 
	return m_min.top();
}

int main()
{
	StackWithMin<int> s;
	s.push(3);
	cout << s.min() << endl;
	s.push(4);
	cout << s.min() << endl;
	s.push(2);
	cout << s.min() << endl;
	s.push(6);
	cout << s.min() << endl;
	s.push(1);
	cout << s.min() << endl;
	cout << "-------------删除-----------------" << endl;
	s.pop();
	cout << s.min() << endl;
	s.pop();
	cout << s.min() << endl;
	s.pop();
	cout << s.min() << endl;
	s.pop();
	cout << s.min() << endl;
	s.pop();
	cout << s.min() << endl;
}
