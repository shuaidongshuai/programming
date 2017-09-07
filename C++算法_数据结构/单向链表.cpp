#include <iostream>
#include <string>
using namespace std;

typedef struct Student{
	int age;
	string name;
	struct Student* next;
}List;

List* init()
{
	List* head = new List;
	List* p = head;
	int b;
	char stop;
	cout<<"初始化单向链表(年龄后面加上$就结束初始化)"<<endl;
	while(stop != '$')
	{
		cout<<"请输入学生姓名，年龄"<<endl;
		List* node = new List;
		cin>>node->name>>node->age;
		node->next = NULL;
		p->next = node;
		p = node;
		stop = getchar();//这里有个小技巧，年龄是整形 
	}
	return head;
}
//头插法 
void addLast(List* head)
{
	List* p = head->next;
	List* node = new List;
	while(p->next!=NULL)
	{
		p = p->next;
	}
	
	cout<<"输入名字 年龄"<<endl;
	
	cin>>node->name>>node->age;
	node->next = NULL; 
	p->next = node;
	//cout<<p->name<<p->age;
}
//尾插法 
void addFirst(List* head)
{
	List* p = head->next;
	List* node = new List;
	cout<<"输入名字 年龄"<<endl;
	cin>>node->name>>node->age;
	head->next = node;
	node->next = p;
} 
//按值删除 
void mydelete(List* head)
{
	List* p = head->next;
	List* prev = head;
	string name;
	cout<<"你要删除哪个人的信息？(请输入姓名)"<<endl; 
	cin>>name; 
	while(p->name!=name)
	{
		prev = p;
		p = p->next;
		
		if(p==NULL)
		{
			cout<<"没有这个人"<<endl;
			return ; 
		}
	}
	prev->next = p->next;
	delete p;
}
//按序删除 
void mydeleteNum(List* head) 
{
	List* p = head->next;
	List* pre = head;
	int n;
	cout<<"你要删除哪个人？(请输入序号)"<<endl; 
	cin>>n; 
	if(n>0)
	{
		while(n-->1)
		{
			pre = p;
			p = p->next;
		}
		pre->next = p->next;
		delete p;
	}
}
//改 
void alter(List* head)
{
	List* p = head->next;
	List* last = p->next;
	string name;
	cout<<"你要改哪个人的信息？(请输入姓名)"<<endl; 
	cin>>name; 
	
	while(p->name!=name)
	{
		p = p->next;
		if(p==NULL)
			return;
		last = p->next;
	}
	
	cout<<"请输入新的名字和年龄"<<endl;
	cin>>p->name>>p->age;
}
//查找 
void check(List* head)
{
	List* p = head->next;
	string name;
	cout<<"你要找哪个人？(请输入姓名)"<<endl; 
	cin>>name; 
	while(p->name!=name)
	{
		p = p->next;
		
		if(p==NULL)
		break;
	}
	if(p!=NULL)
		cout<<"有这个人，他的名字是"<<p->name<<"\t年龄是"<<p->age<<endl;
	else
		cout<<"没有这个人"<<endl;
}
void display(List* head)
{
	List* p = head->next;
	int n = 1;
	while(p!=NULL)
	{
		cout<<n++<<"☆"<<"姓名："<<p->name<<"\t年龄："<<p->age<<endl;
		p = p->next;
	}
}

int main()
{
	List* head = init();
	int n = 0;
	while(1)
	{
		cout<<"1.头插\t2.尾插\t3.按值删除\t4.按序删除\t5.改\t6.查找\t7.显示"<<endl;
		cin>>n;
		
		if(1 == n)
		{
			addFirst(head);
		}
		else if(2 == n)
		{
			addLast(head);
		}
		else if(3 == n)
		{
			mydelete(head);
		}
		else if(4 == n)
		{
			mydeleteNum(head);
		}
		else if(5 == n)
		{
			alter(head);
		}
		else if(6 == n)
		{
			check(head);
		}
		else if(7 == n)
		{
			display(head); 
		}
		else if(n<='0' || n>'7')
		{
			cout<<"请正确输入"<<endl; 
			break;
		}
	}
	
}
/*
陈明东 20
金莎 32
帅东 22
成龙 44
赵丽颖 27
Baby 28$ 
*/
