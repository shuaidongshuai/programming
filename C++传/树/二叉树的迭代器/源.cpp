#include<iostream>
#include<stack>
#include<queue>
using namespace std;

template<class _Ty>
const _Ty & Max(const _Ty &a, const _Ty &b)
{
	return a>b ? a : b;
}

template<class _Ty>
class BinaryTree
{
public:
	struct _Node;
	typedef struct _Node *_Nodeptr;
	struct _Node
	{
		_Nodeptr leftchild, rightchild;
		_Ty      data;
	};
	_Nodeptr Create(_Ty *&str)
	{
		_Nodeptr s = NULL;
		if (*str != refvalue)
		{
			s = _Buynode();
			s->data = *str;
			s->leftchild = Create(++str);
			s->rightchild = Create(++str);
		}
		return s;
	}
	static void PreOrder(_Nodeptr p)
	{
		if (p != NULL)
		{
			cout << p->data << " ";
			PreOrder(p->leftchild);
			PreOrder(p->rightchild);
		}
	}
	static void InOrder(_Nodeptr p)
	{
		if (p != NULL)
		{
			InOrder(p->leftchild);
			cout << p->data << " ";
			InOrder(p->rightchild);
		}
	}
	static void PastOrder(_Nodeptr p)
	{
		if (p != NULL)
		{
			PastOrder(p->leftchild);
			PastOrder(p->rightchild);
			cout << p->data << " ";
		}
	}
	static int size(_Nodeptr p)
	{
		if (NULL == p) return 0;
		else return size(p->leftchild) + size(p->rightchild) + 1;
	}
	static int depth(_Nodeptr p)
	{
		if (NULL == p) return 0;
		else return Max(depth(p->leftchild), depth(p->rightchild)) + 1;
	}
	static _Nodeptr FindValue(_Nodeptr p, const _Ty &x)
	{
		if (p == NULL || p->data == x) return p;
		else
		{
			_Nodeptr s = FindValue(p->leftchild, x);
			if (NULL == s)
			{
				s = FindValue(p->rightchild, x);
			}
			return s;
		}
	}
	static _Nodeptr Copy(_Nodeptr ptr)
	{
		_Nodeptr s = NULL;
		if (ptr != NULL)
		{
			s = _Buynode();
			s->data = ptr->data;
			s->leftchild = Copy(ptr->leftchild);
			s->rightchild = Copy(ptr->rightchild);
		}
		return s;
	}
	static void destroy(_Nodeptr p)
	{
		if (p != NULL)
		{
			destroy(p->leftchild);
			destroy(p->rightchild);
			_Freenode(p);
		}
	}
	static bool equal(_Nodeptr pa, _Nodeptr pb)
	{
		return ((pa == NULL && pb == NULL) ||
			(pa != NULL && pb != NULL &&
			pa->data == pb->data &&
			equal(pa->leftchild, pb->leftchild) &&
			equal(pa->rigthchild, pb->rightchild)));

	}
public:
	BinaryTree(const _Ty &x) :root(NULL), refvalue(x) {}
	BinaryTree(const BinaryTree<_Ty> &bt)
	{
		root = Copy(bt.root);
		refvalue = bt.refvalue;
	}
	BinaryTree<_Ty> & operator=(const BinaryTree<_Ty> &bt)
	{
		if (this != &bt)
		{
			destroy(root);
			root = Copy(bt.root);
		}
		return *this;
	}
	~BinaryTree()
	{
		clear();
	}
	void clear()
	{
		destroy(root);
		root = NULL;
	}

	void CreateTree(_Ty *str)
	{
		if (str != NULL)
		{
			root = Create(str);
		}
	}
	void PreOrder() const
	{
		PreOrder(root);
		cout << endl;
	}
	void InOrder() const
	{
		InOrder(root);
		cout << endl;
	}
	void PastOrder() const
	{
		PastOrder(root);
		cout << endl;
	}
	int size() const
	{
		return size(root);
	}
	int depth() const
	{
		return depth(root);
	}
	_Nodeptr GetRoot() const { return root; }
	_Nodeptr FindValue(const _Ty &v) const
	{
		return FindValue(root, v);
	}

	bool operator==(const BinaryTree<_Ty> &bt) const
	{
		return equal(this->root, bt.root);
	}
	bool operator!=(const BinaryTree<_Ty> &bt) const
	{
		return !(*this == bt);
	}
private:
	static _Nodeptr _Buynode()
	{
		_Nodeptr s = (_Nodeptr)malloc(sizeof(_Node));
		if (NULL == s) exit(1);
		memset(s, 0, sizeof(_Node));
		return s;
	}
	static void _Freenode(_Nodeptr p)
	{
		free(p);
	}
	_Nodeptr root;
	_Ty  refvalue; // end;
};

///////////////////////////////////////////////
template<class _Ty>
class TreeIterator
{
protected:
	BinaryTree<char>::_Nodeptr _Ptr;
	BinaryTree<char> &tree;
public:
	TreeIterator(BinaryTree<_Ty> &bt) :_Ptr(NULL), tree(bt) {}
	virtual ~TreeIterator() {}
	bool IsDone() const { return _Ptr == NULL; }
	_Ty & operator*(){ return _Ptr->data; }
	const _Ty & operator*() const { return _Ptr->data; }
	virtual void First() = 0;
	virtual void operator++() = 0;
};
template<class _Ty>
struct StkNode
{
	BinaryTree<char>::_Nodeptr node;
	int times;
public:
	StkNode(BinaryTree<char>::_Nodeptr _P = NULL)
		:node(_P), times(0)
	{}
};
//后序遍历
template<class _Ty>
class PastIterator : public TreeIterator<_Ty>
{
protected:
	stack<StkNode<_Ty> > st;
public:
	PastIterator(BinaryTree<_Ty> &bt) :TreeIterator<_Ty>(bt) {}
	~PastIterator() {}
	void First()
	{
		StkNode<_Ty> stknode(tree.GetRoot());
		st.push(stknode);
		++(*this);
	}
	void operator++()
	{
		StkNode<_Ty> stknode;
		while (!st.empty())
		{
			stknode = st.top();
			st.pop();
			if (++stknode.times == 3)
			{
				_Ptr = stknode.node;
				return;
			}

			if (stknode.times == 1)
			{
				st.push(stknode);
				if (stknode.node->leftchild != NULL)
					st.push(StkNode<_Ty>(stknode.node->leftchild));
			}
			else if (stknode.times == 2)
			{
				st.push(stknode);
				if (stknode.node->rightchild != NULL)
					st.push(StkNode<_Ty>(stknode.node->rightchild));
			}
		}
		_Ptr = NULL;
	}
};
//先序遍历
template<class _Ty>
class PreIterator : public TreeIterator<_Ty>
{
protected:
	stack<StkNode<_Ty> > st;
public:
	PreIterator(BinaryTree<_Ty> &bt) :TreeIterator<_Ty>(bt) {}
	void First()
	{
		StkNode<_Ty> stknode(tree.GetRoot());
		st.push(stknode);
		++(*this);
	}
	void operator++()
	{
		StkNode<_Ty> stknode;
		while (!st.empty())
		{
			stknode = st.top();
			st.pop();
			if (++stknode.times == 1)
			{
				st.push(stknode);
				if (stknode.node->leftchild != NULL)
					st.push(StkNode<_Ty>(stknode.node->leftchild));
				_Ptr = stknode.node;
				return;
			}
			else if (stknode.times == 2)
			{
				st.push(stknode);
				if (stknode.node->rightchild != NULL)
					st.push(StkNode<_Ty>(stknode.node->rightchild));
			}
		}
		_Ptr = NULL;
	}
};
//中序遍历
template<class _Ty>
class InIterator : public TreeIterator<_Ty>
{
protected:
	stack<StkNode<_Ty> > st;
public:
	InIterator(BinaryTree<_Ty> &bt) :TreeIterator<_Ty>(bt) {}
	void First()
	{
		StkNode<_Ty> stknode(tree.GetRoot());
		st.push(stknode);
		++(*this);
	}
	void operator++()
	{
		StkNode<_Ty> stknode;
		while (!st.empty())
		{
			stknode = st.top();
			st.pop();
			if (++stknode.times == 1)
			{
				st.push(stknode);
				if (stknode.node->leftchild != NULL)
					st.push(StkNode<_Ty>(stknode.node->leftchild));
			}
			else if (stknode.times == 2)
			{
				st.push(stknode);
				if (stknode.node->rightchild != NULL)
					st.push(StkNode<_Ty>(stknode.node->rightchild));
				_Ptr = stknode.node;
				return;
			}
		}
		_Ptr = NULL;
	}
};
//换一种思路做
template<class _Ty>
class InIterator2 : public TreeIterator<_Ty>
{
protected:
	stack<BinaryTree<char>::_Nodeptr> st;
	BinaryTree<char>::_Nodeptr pNode;
public:
	InIterator2(BinaryTree<_Ty> &bt) :TreeIterator<_Ty>(bt) {}
	void First()
	{
		pNode = tree.GetRoot();
		operator++();
	}
	void operator++()
	{
		/*和非递归中序遍历一样的，只是打印换成了_Ptr = 打印的值*/
		if (!st.empty() || pNode)
		{
			while (pNode)
			{
				st.push(pNode);
				pNode = pNode->leftchild;
			}
			_Ptr = st.top();
			st.pop();
			pNode = _Ptr->rightchild;
		}
		else
			_Ptr = NULL;
	}
};
//层次遍历
template<class _Ty>
class LevelIterator : public TreeIterator<_Ty>
{
protected:
	queue<StkNode<_Ty> > st;
public:
	LevelIterator(BinaryTree<_Ty> &bt) :TreeIterator<_Ty>(bt) {}
	void First()
	{
		StkNode<_Ty> stknode(tree.GetRoot());
		st.push(stknode);
		++(*this);
	}
	void operator++()
	{
		StkNode<_Ty> stknode;
		if(!st.empty())
		{
			stknode = st.front();
			st.pop();
			if (stknode.node->leftchild != NULL)
				st.push(stknode.node->leftchild);
			if (stknode.node->rightchild != NULL)
				st.push(stknode.node->rightchild);
			_Ptr = stknode.node;
			return;
		}
		_Ptr = NULL;
	}
};
void main()
{
	char *str = "ABC##DE##F##G#H##";
	int ar[] = { 12, 23, 34, -1, -1, 45, 56, -1, -1, 67, -1, -1, 78, -1, 89, -1, -1 };
	BinaryTree<char> cmyt('#');
	cmyt.CreateTree(str);
	
	cout << "后序遍历" << endl;
	PastIterator<char> pt(cmyt);
	pt.First(); // _Ptr 
	while (!pt.IsDone())
	{
		cout << *pt << " ";
		++pt;
	}
	cout << endl << "----------------------------------------" << endl;

	cout << "先序遍历" << endl;
	PreIterator<char> pt2(cmyt);
	pt2.First(); // _Ptr 
	while (!pt2.IsDone())
	{
		cout << *pt2 << " ";
		++pt2;
	}
	cout << endl << "----------------------------------------" << endl;

	cout << "中序遍历" << endl;
	InIterator<char> pt5(cmyt);
	pt5.First(); // _Ptr 
	while (!pt5.IsDone())
	{
		cout << *pt5 << " ";
		++pt5;
	}
	cout << endl << "----------------------------------------" << endl;

	cout << "中序遍历 第二种方法" << endl;
	InIterator2<char> pt3(cmyt);
	pt3.First(); // _Ptr 
	while (!pt3.IsDone())
	{
		cout << *pt3 << " ";
		++pt3;
	}
	cout << endl << "----------------------------------------" << endl;

	cout << "层次遍历" << endl;
	LevelIterator<char> pt4(cmyt);
	pt4.First(); // _Ptr 
	while (!pt4.IsDone())
	{
		cout << *pt4 << " ";
		++pt4;
	}
	cout << endl << "----------------------------------------" << endl;

	system("pause");
}
