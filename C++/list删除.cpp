/* list删除val为双数的节点（迭代器失效的问题）*/
#include <iostream>
#include <list>
using namespace std;

template<typename T>
void DelDoubleNode(list<T> &myList){
	int i = 1;
	for(auto it = myList.begin(); it != myList.end(); ++i){
		if((i & 1) == 0){
			myList.erase(it++);
		}
		else
			++it;
	}
}

int main(){
	list<int> li;
	for(int i = 1; i < 10; ++i){
		li.push_back(i); 
	}
	DelDoubleNode<int>(li);
	for(auto it = li.begin(); it != li.end(); ++it){
		cout<< *it << " ";
	}
}
