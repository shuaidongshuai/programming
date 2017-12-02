#include<iostream>
using namespace std;

#include"yhp_list.h"

/*
class String
{
	char *str;
public:
	String(char *p = NULL)
	{
		if(p != NULL)
		{
			str = (char*)malloc(sizeof(char)*strlen(p)+1);
			strcpy(str,p);
		}
		else
		{
			str = new char[1];
			str[0] = '\0';
		}
	}
	~String()
	{
		free(str);
		str = NULL;
	}
};
class Test
{
public:
	int value;
public:
	Test(int x=0):value(x) {}
	virtual void print() const { cout<<"Test::print"<<endl;}
	void show() const { cout<<"Test::show: "<<value<<endl;}
	~Test() {}
};
void main()
{
	Test *p = (Test*)malloc(sizeof(Test));
	Test t1;
	new(p) Test(t1);
	p->print();
	p->show();
}
void main()
{
	Test tar[1000];
	Test *p = (Test*)malloc(sizeof(Test)*1000);

	memcpy(p,tar,sizeof(Test)*1000);
	for(int i = 0;i<1000;++i)
	{
		//p[i] = tar[i];
		new(&p[i]) Test(tar[i]);
	}


}

class Base
{
public:
	Base() {}
	Base(const Base &) {}
	Base & operator=(const Base &it)
	{
		return *this;
	}
	~Base() {}
};

class Test 
{
public:
	int value;
public:
	virtual void fun() {}
};

void main()
{
	Test t1, t2;
	t1.value = 20;
	Test t3(t1);
	t1.value = 10;
	t2 = t1;
	t2.~Test();
}

*/
void main()
{
	int ar[]={12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar)/sizeof(ar[0]);
	int *p = ar;
	const int *s = ar;
	yhp::list<int> mylist;
	mylist.insert(mylist.begin(),ar,ar+n);
	yhp::list<int>::iterator it = mylist.begin();
	
	cout<<*it<<endl;
	yhp::advance(it,5);
	cout<<*it<<endl;
	yhp::advance(p,5);
	cout<<*p<<endl;
	yhp::advance(s,5);
	system("pause");
}
