#include <iostream>
#include <stack>
using namespace std;
//写代码反转栈，不能重新用一个栈，不能用数组，只能用递归

//这个比较难 http://www.cnblogs.com/4everlove/p/3666016.html
void ReverseStack(stack<int> &s){
	if(s.empty() || s.size() == 1)
		return;
	int top = s.top();
	s.pop();
	ReverseStack(s);//这次反转只为拿到最下面的元素 
	int bottom = s.top();
	s.pop();
	ReverseStack(s);//让栈还原 
	s.push(top);
	ReverseStack(s);//反转栈让最下面的元素到最上面
	s.push(bottom);
}
//这个比较简单  加一个新的函数，用来把顶端元素放到最下面
void PushBack(stack<int> &s, int size, int num){
	if(size == 0){
		s.push(num);
		return;
	}
	int top = s.top();
	s.pop();
	PushBack(s, size - 1, num);
	s.push(top);
}
void ReverseStack2(stack<int> &s, int size){
	if(s.empty() || size <= 1)
		return;
	int top = s.top();
	s.pop();
	PushBack(s, size - 1, top);
	ReverseStack2(s, size - 1);
} 
int main(){
    stack<int> s;
    s.push(0);
    s.push(1);
    s.push(2);
    s.push(3);
    ReverseStack2(s,s.size());
    while(!s.empty()){
    	cout<<s.top()<<endl;
    	s.pop();
	}
}
