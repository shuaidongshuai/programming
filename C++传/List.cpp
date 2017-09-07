//	Lists将元素按顺序储存在链表中. 与 向量(vectors)相比, 它允许快速的插入和删除，但是随机访问却比较慢.
//	
//	assign() 给list赋值 						翻译：分配
//	back() 返回最后一个元素 
//	begin() 返回指向第一个元素的迭代器 
//	clear() 删除所有元素 
//	empty() 如果list是空的则返回true 
//	end() 返回末尾的迭代器 
//	erase() 删除一个元素 
//	front() 返回第一个元素 
//	get_allocator() 返回list的配置器 
//	insert() 插入一个元素到list中 
//	max_size() 返回list能容纳的最大元素数量 
//	merge() 合并两个list 
//	pop_back() 删除最后一个元素 
//	pop_front() 删除第一个元素 
//	push_back() 在list的末尾添加一个元素 
//	push_front() 在list的头部添加一个元素 
//	rbegin() 返回指向第一个元素的逆向迭代器 
//	remove() 从list删除元素 
//	remove_if() 按指定条件删除元素 
//	rend() 指向list末尾的逆向迭代器 
//	resize() 改变list的大小 
//	reverse() 把list的元素倒转 
//	size() 返回list中的元素个数 
//	sort() 给list排序 
//	splice() 合并两个list 
//	swap() 交换两个list 
//	unique() 删除list中重复的元素

#include <iostream>
#include <list>
#include <numeric>  
#include <algorithm>   
using namespace std;  

void pForward(list<int> l)
{
	//正向遍历 
	for(list<int>::iterator i = l.begin();i!=l.end();i++)
	{
		cout<<*i<<"\t";
	}
	cout<<endl;
}
void pReverse(list<int> l)
{
	//反向遍历 
	for(list<int>::reverse_iterator i = l.rbegin();i!=l.rend();i++)
	{
		cout<<*i<<"\t";
	}
	cout<<endl;
}

int main1()
{
	//list1对象初始为空   
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_front(4);
	l.push_front(6);
	
	pForward(l);
	
	pReverse(l);
	
	//使用STL的accumulate(累加)算法   需要#include <numeric>    参数：1.第一个迭代的值 2.最后一个迭代值 3.前面计算得到结果 
	int res = accumulate(l.begin(),l.end(),0);
	cout<<"总和："<<res<<endl;
	
	list<int>::iterator i = max_element(l.begin(),l.end());
	cout<<"最大的数"<<*i<<endl;
}
int main()
{
	list<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);
	//list2对象最初有10个值为6的元素  
	list<int> list2(10,6);
	pForward(list2);
	
	//list3对象最初有3个值为6的元素   
    list<int> list3(list1.begin(),--list1.end());//初始化：从list1 的第一个数到 倒数第二个数 
    pForward(list3);
    
    //在list1序列中间插入数据   
    list1.insert(++list1.begin(),3,9);//在第二个位置，插入3个9 
	pForward(list1);
	
	//测试引用类函数   
    cout<<"list1.front()="<<list1.front()<<endl;   
    cout<<"list1.back()="<<list1.back()<<endl;   
    
    //从list1序列的前后各移去一个元素   
    list1.pop_front();   
    list1.pop_back();   
    cout<<"list1序列的前后各移去一个元素 "<<endl;   
    pForward(list1);
	
	 //清除list1中的第2个元素   
    list1.erase(++++++list1.begin());   
    cout<<"清除list1中的第4个元素 "<<endl;   
    pForward(list1);      
    
    //对list1容器排序   
    list1.sort();   
    cout<<"对list1容器排序 "<<endl;  
    pForward(list1); 
    
     //对list2赋值并显示   
    list2.assign(8,1);   
    cout<<"对list2赋值并显示 "<<endl;   
    pForward(list2); 
    
    //splice() 合并两个list 
    list1.splice(++++list1.begin(), list2);//从list1 的第三个位置开始合并，，就是说list1的第三个位置以后都是list2  然后再是list1剩下的数 
    cout<<"合并两个list"<<endl;
    pForward(list1); 

}


