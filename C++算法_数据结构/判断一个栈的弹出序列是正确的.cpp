#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

template<class T>
bool IsPopOrder(T *pPush,T *pPop,int len)
{
	if(!pPush || !pPop || len < 0)
		return false;
	stack<T> s;
	int *firstPush = pPush;
	int *firstPop = pPop;
	while(pPop - firstPop < len)		//这个算是学到了，指针可以相减啊，搞得我一开始用定时器好low 
	{
		while(*pPush != *pPop)
		{
			if(pPush - firstPush >= len) 
				return false;
			s.push(*pPush);
			pPush++;
		}
		pPush++;
		pPop++;
		while(!s.empty() && s.top() == *pPop)
		{
			pPop++;
			s.pop();
		}
	}
	return true;
}

int main()
{
	int push[] = {1,2,3,4,5};
	int pop1[] = {4,5,3,2,1};//1
	cout<<IsPopOrder<int>(push,pop1,sizeof(push)/sizeof(push[0]))<<endl;
	
	int pop2[] = {4,3,5,1,2};//0
	cout<<IsPopOrder<int>(push,pop2,sizeof(push)/sizeof(push[0]))<<endl;
	
	int pop3[] = {4,3,2,5,1};//1
	cout<<IsPopOrder<int>(push,pop3,sizeof(push)/sizeof(push[0]))<<endl;
} 
