#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
using namespace std;
/* 插入 删除 迭代器失效问题 */
template<typename T>
void print(T t){
	for(auto it = t.begin(); it != t.end(); ++it)
		cout<<*it<<" ";
	cout<<endl;
}
void testVec(){
	vector<int> v(4);
	cout<<"原数组"<<endl;
	print(v);
	cout<<"增加元素6"<<endl;
	for(auto it = v.begin(); it != v.end(); ++it){
		if(0 == *it){
			it = v.insert(it, 6);//迭代器会失效 返回值是当前插入的元素  注意：插入是在it前面 所以要++两次 
			++it;
		}
	}
	print(v);
	cout<<"删除元素0"<<endl;
	for(auto it = v.begin(); it != v.end();){
		if(0 == *it)
			it = v.erase(it);//失效 it指向删除元素 返回下一个元素 
		else
			++it;
	}
	print(v);
}
void testList(){
	list<int> l(4);
	cout<<"原list"<<endl;
	print(l);
	cout<<"增加元素6"<<endl;
	for(auto it = l.begin(); it != l.end(); ++it){
		if(0 == *it)
			l.insert(it, 6);//迭代器不失效 it指向原来的元素 
	}
	print(l);
	cout<<"删除元素0"<<endl;
	for(auto it = l.begin(); it != l.end();){
		if(0 == *it)
			it = l.erase(it);//失效 it指向删除元素 返回下一个元素 
		else
			++it;
	}
	print(l);
	cout<<"删除元素6"<<endl;
	for(auto it = l.begin(); it != l.end();){
		if(6 == *it)
			l.erase(it++);//失效 it提前跳到下一个元素  只有底层是链表结构可以 
		else
			++it;
	}
	print(l);
}
void testDeque(){
	deque<int> d(4);
	cout<<"原deque"<<endl;
	print(d);
	cout<<"增加元素6"<<endl;
	for(auto it = d.begin(); it != d.end(); ++it){
		if(0 == *it){
			it = d.insert(it, 6);//迭代器会失效 返回值是当前插入的元素  注意：插入是在it前面 所以要++两次 
			++it;
		}
	}
	print(d);
	cout<<"删除元素0"<<endl;
	for(auto it = d.begin(); it != d.end();){
		if(0 == *it)
			it = d.erase(it);//失效 it指向删除元素 返回下一个元素 
		else
			++it;
	}
	print(d);
}
void testSet(){
	set<int> s;
	for(int i = 0; i < 3; ++i)
		s.insert(i);
	cout<<"原set"<<endl;
	print(s);
	cout<<"增加元素6 迭代器指向->";
	for(auto it = s.begin(); it != s.end(); ++it){
		if(1 == *it){
			s.insert(it, 6);//迭代器不失效 it指向当前元素  
			cout<<*it<<endl;
		}
	}
	print(s);
	cout<<"删除元素6"<<endl;
	for(auto it = s.begin(); it != s.end();){
		if(6 == *it)
			it = s.erase(it);//失效 it指向删除元素 返回下一个元素 
		else
			++it;
	}
	print(s);
	cout<<"删除元素1"<<endl;
	for(auto it = s.begin(); it != s.end();){
		if(1 == *it)
			s.erase(it++);//失效 it提前跳到下一个元素  只有底层是链表结构可以 
		else
			++it;
	}
	print(s);
}
template<typename T>
void printMap(T t){
	for(auto it = t.begin(); it != t.end(); ++it)
		cout<<"["<<it->first<<"]"<<it->second<<"\t";
	cout<<endl;
}
void testMap(){
	map<int, int> m;
	m[1] = 10;
	m[2] = 20;
	m[3] = 30;
	printMap(m);
	cout<<"增加key6"<<endl;
	/* 完全没有必要弄一个循环 因为底层都是红黑树形式 当前迭代器在哪都无所谓 只是为了说明insert迭代器不失效
		insert(it, 6) 底层调用了insert(6) 
	 */
	for(auto it = m.begin(); it != m.end(); ++it){
		if(2 == it->first)
			m.insert(it, pair<int, int>(6, 60));//insert的效率比【】高
	}
	printMap(m);
	cout<<"删除key6"<<endl;
	for(auto it = m.begin(); it != m.end();){
		if(6 == it->first)
			m.erase(it++);//失效 it提前跳到下一个元素  只有底层是链表结构可以 
		else
			++it;
	}
	printMap(m);
}
int main(){
	cout<<"------------vector------------"<<endl;
	testVec();
	cout<<"-------------list-----------"<<endl;
	testList(); 
	cout<<"-------------Deque-----------"<<endl;
	testDeque();
	cout<<"--------------Set----------"<<endl;
	testSet();
	cout<<"--------------Map----------"<<endl;
	testMap();
}
/*
总结：
vector:插入和删除元素都会使迭代器失效
deque:插入和删除元素都会使迭代器失效
list:插入，迭代器不会失效。删除，指向被删除节点迭代器失效
set:插入，迭代器不会失效。删除，指向被删除节点迭代器失效
map:插入，迭代器不会失效。删除，指向被删除节点迭代器失效
*/ 
