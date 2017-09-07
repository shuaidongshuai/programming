#include <iostream> 

using namespace std;

class Link
{
public:
	Link() :_phead(new Node){}
	~Link()
	{
		Node *next = _phead->_pnext;
		while (_phead)
		{
			delete _phead;
			_phead = next;
			next = next->_pnext;
		}
	}
	void insertHead(int val)
	{
		Node *node = new Node(val);
		node->_pnext = _phead->_pnext;
		_phead->_pnext = node;
	}
	void insertTail(int val)
	{
		Node *p = _phead;
		while (p->_pnext)
			p = p->_pnext;
		Node *node = new Node(val);
		p->_pnext = node;
		node->_pnext = 0;
	}
	void deleteNode(int val)
	{
		Node *pre = _phead;
		Node *node = pre->_pnext;
		while (node)
		{
			if (node->_data == val)
			{
				pre->_pnext = node->_pnext;
				delete node;
				break;
			}
			pre = node;
			node = node->_pnext;
		}
	}
	void showLink()
	{
		Node *p = _phead->_pnext;
		while (p)
		{
			cout << p->_data << " ";
			p = p->_pnext;
		}
		cout << endl;
	}
	/*合并有序单链表*/
	void mergeLink(Link *&src)
	{
		Node *pre1 = _phead;
		Node *pre2 = src->_phead;
		Node *node1 = pre1->_pnext;
		Node *node2 = pre2->_pnext;
		while (node1 && node2)
		{
			pre2 = node2;
			node2 = node2->_pnext;
			if (node1->_data > pre2->_data)
			{
				pre1->_pnext = pre2;
				pre2->_pnext = node1;
				pre1 = node1;
				node1 = node1->_pnext;
			}
			else
			{
				pre2->_pnext = node1->_pnext;
				node1->_pnext = pre2;
				pre1 = pre2;
				node1 = pre1->_pnext;
			}
		}
	}
	/*倒数第K个*/
	int get_last_node(int k)
	{
		if (k < 0)
			return 0;
		Node *cur = _phead->_pnext;
		Node *knode = cur;
		while (k--)
			knode = knode->_pnext;
		while (knode)
		{
			cur = cur->_pnext;
			knode = knode->_pnext;
		}
		return cur->_data;
	}
	/*逆置*/
	void reverse()
	{
		Node *pre = NULL;
		Node *node = _phead->_pnext;
		if (!node)
			return;
		Node *next = node->_pnext;
		while (node)
		{
			node->_pnext = pre;
			pre = node;
			node = next;
			if (node)
				next = next->_pnext;
		}
		_phead->_pnext = pre;
	}
private:
	class Node
	{
	public:
		Node(int data = 0) :_data(data), _pnext(0){}
		int _data;
		Node *_pnext;
	};
	Node *_phead;
};

int main()
{
	Link *link1 = new Link;
	Link *link2 = new Link;
	for (int i = 0; i < 13; i += 3)
		link1->insertTail(i);
	for (int i = 1; i < 10; i += 2)
		link2->insertTail(i);
	link1->showLink();
	link2->showLink();

	link1->mergeLink(link2);
	link1->showLink();

	cout << link1->get_last_node(2) << endl;

	link1->reverse();
	link1->showLink();

	return 0;
}
