#include <iostream>
#include <queue>
using namespace std; 

int main2()
{
	queue<char> q;
	for(char i = 'A';i<='Z';i++)
	{
		q.push(i);//在末尾加一个元素 
		cout<<q.back()<<"   ";//返回最后一个元素  
	}
	cout<<endl;
	while(!q.empty())
	{
		cout<<q.front()<<"   ";//返回第一个元素 
		q.pop();//删除第一个元素 
	}
	cout<<endl;
}
int main()
{
	queue<int> q;
	q.push(1);
	q.push(2);
	q.front() = 5;
	cout<<q.front()<<endl;
	cout<<q.back()<<endl;
}
