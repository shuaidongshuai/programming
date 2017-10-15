#include<iostream>
#include<stack>
#include<queue>
using namespace std;

typedef int KeyType;
typedef struct BstNode
{
	BstNode * parent;
	BstNode * leftchild;
	BstNode * rightchild;
	KeyType key;
}BstNode, *BSTree;

BstNode * _Buynode()
{
	BstNode *s = (BstNode*)malloc(sizeof(BstNode));
	if (s == NULL) exit(1);
	memset(s, 0, sizeof(BstNode));
	return s;
}
BstNode * FindValue(BstNode *ptr, KeyType kx)
{
	while (ptr != NULL && ptr->key != kx)
	{
		ptr = kx < ptr->key ? ptr->leftchild : ptr->rightchild;
	}
	return ptr;
}
BstNode * SearchValue(BstNode *ptr, KeyType kx)
{
	if (ptr == NULL || ptr->key == kx)
		return ptr;
	else if (kx<ptr->key)
		return SearchValue(ptr->leftchild, kx);
	else
		return SearchValue(ptr->rightchild, kx);
}
/////////////////////////////////////非递归插入////////////////////////////////////////////////////
bool Insert(BSTree *ptree, KeyType kx)
{
	if (ptree == NULL) return false;
	if (*ptree == NULL)
	{
		BstNode * s = _Buynode();
		s->parent = s->leftchild = s->rightchild = NULL;
		s->key = kx;
		*ptree = s;
		return true;
	}
	BstNode *pa = NULL;
	BstNode *p = *ptree;
	while (p)
	{
		pa = p;
		if (p->key == kx)
			return false;
		else if (p->key > kx)
			p = p->leftchild;
		else
			p = p->rightchild;
	}
	BstNode * s = _Buynode();
	s->key = kx;
	if (pa->key > kx)
		pa->leftchild = s;
	else
		pa->rightchild = s;
	s->parent = pa;
	return true;
}
bool Insert2(BSTree *ptree, KeyType kx)
{
	if (ptree == NULL) return false;
	BstNode *pa = NULL;
	BstNode *p = *ptree;
	while (p)
	{
		pa = p;
		if (p->key == kx)
			return false;
		else if (p->key > kx)
			p = p->leftchild;
		else
			p = p->rightchild;
	}
	BstNode * s = _Buynode();
	s->key = kx;
	if (pa)
	{
		if (pa->key > kx)
			pa->leftchild = s;
		else
			pa->rightchild = s;
		s->parent = pa;
	}
	else
	{
		s->parent = s->leftchild = s->rightchild = NULL;
		p = s;
	}
	return true;
}
/////////////////////////////////////递归插入////////////////////////////////////////////////////
bool Insert3(BstNode *&ptr, KeyType &x, BstNode *pa)
{
	bool res = false;
	if (!ptr)
	{
		ptr = _Buynode();
		ptr->key = x;
		ptr->parent = pa;
		res = true;
	}
	else if (ptr->key > x)
	{
		res = Insert3(ptr->leftchild, x, ptr);
	}
	else if (ptr->key < x)
	{
		res = Insert3(ptr->rightchild, x, ptr);
	}
	return res;
}
//////////////////////////////////////////递归中序遍历////////////////////////////////////////////////////////////
void InOrder(BstNode *p)
{
	if (p != NULL)
	{
		InOrder(p->leftchild);
		cout << p->key << " ";
		InOrder(p->rightchild);
	}
}
//////////////////////////////////////////非递归中序遍历1////////////////////////////////////////////////////////////
void NiceInOrder(BstNode *ptr)
{
	KeyType rootVal = ptr->key;
	BstNode *pre = new BstNode;
	BstNode *b = ptr;
	if (!ptr) return;
	while (b->rightchild)
		b = b->rightchild;
	while (1)
	{
		while (ptr->leftchild)
			ptr = ptr->leftchild;
		cout << ptr->key << " ";
		if (ptr->key == b->key)
			return;
		pre = ptr;
		ptr = ptr->rightchild;
		/* 该节点为NULL就需要找到他的下一个节点，根据父节点向上找 */
		while (!ptr)
		{
			/* 为啥要加一个pre->parent呢？ 答：root节点没有父节点 */
			while (pre->parent && pre->key > pre->parent->key)//一定要父节点的键值大于当前key才能停，只有大于当前key说明这个父节点没有被打印过
				pre = pre->parent;
			if (pre->parent)
				pre = pre->parent;
			cout << pre->key << " ";
			if (pre->key == b->key)
				return;
			ptr = pre->rightchild;
		}
	}
}
//////////////////////////////////////////非递归中序遍历2////////////////////////////////////////////////////////////
BstNode *First(BstNode *p)
{
	while (p->leftchild)
		p = p->leftchild;
	return p;
}
BstNode *Next(BstNode *ptr)
{
	if (ptr == NULL) return NULL;
	if (ptr->rightchild)
	{
		return First(ptr->rightchild);
	}
	else
	{
		BstNode *pre = ptr->parent;
		while (pre && ptr->key > pre->key)
		{
			ptr = pre;
			pre = pre->parent;
		}
		return pre;
	}
}
void NiceInOrder2(BstNode *ptr)
{
	for (BstNode *p = First(ptr); p != NULL; p = Next(p))
	{
		cout << p->key << " ";
	}
	cout << endl;
}
/////////////////////////////////////非递归删除////////////////////////////////////////////////////
void remove(BstNode *&ptr, KeyType k)//加引用是为了删除根，不然没法改变根节点
{
	BstNode *node = FindValue(ptr, k);
	if (!node) return;//情况1  没有找到
	if (node->rightchild)//情况2 有右孩子
	{
		BstNode *temp = node->rightchild;
		if (node->parent)
		{
			if (node->parent->key > node->key)
				node->parent->leftchild = node->rightchild;
			else
				node->parent->rightchild = node->rightchild;

			node->rightchild->parent = node->parent;
		}
		else
		{
			ptr = node->rightchild;
			ptr->parent = NULL;
		}
		while (temp->leftchild)
			temp = temp->leftchild;
		temp->leftchild = node->leftchild;
		node->leftchild->parent = temp;
	}
	else if (node->leftchild)//情况3 有左孩子也有右孩子
	{
		if (node->parent->key > node->key)
			node->parent->leftchild = node->leftchild;
		else
			node->parent->rightchild = node->leftchild;
		node->leftchild->parent = node->parent;
	}
	else	//情况4 左右都没有孩子
	{
		if (node->parent->key > node->key)
			node->parent->leftchild = NULL;
		else
			node->parent->rightchild = NULL;
	}
	delete node;
}
/////////////////////////////////////非递归删除2////////////////////////////////////////////////////
bool Remove2(BSTree *ptree, KeyType kx)
{
	if (ptree == NULL || *ptree == NULL) return false;
	BstNode * p = FindValue(*ptree, kx);
	if (p == NULL) return false;

	//左右都不为空
	if (p->leftchild != NULL && p->rightchild != NULL)
	{
		BstNode *s = Next(p);
		p->key = s->key;
		p = s;//把删除双分支情况改为单分支
	}
	//单分支情况
	BstNode *pa = p->parent;
	BstNode *child = p->leftchild != NULL ? p->leftchild : p->rightchild;
	if (child != NULL)
		child->parent = pa;
	if (pa == NULL)
		*ptree = child;
	else
	{
		if (pa->leftchild == p)
			pa->leftchild = child;
		else
			pa->rightchild = child;
	}
	delete p;
	return true;

}
/////////////////////////////////////递归删除////////////////////////////////////////////////////
bool Remove(BstNode *&ptr, int x)
{
	bool res = false;
	if (!ptr) return res;
	if (x < ptr->key)
		res = Remove(ptr->leftchild, x);
	else if (x > ptr->key)
		res = Remove(ptr->rightchild, x);
	else if (ptr->leftchild && ptr->rightchild)
	{
		BstNode* p = Next(ptr);
		ptr->key = p->key;
		res = Remove(ptr->rightchild, ptr->key);
	}
	else
	{
		BstNode *child = ptr->leftchild ? ptr->leftchild : ptr->rightchild;
		if (child)//单分支情况
			child->parent = ptr->parent;

		BstNode *p = ptr;
		ptr = child;
		delete p;
		res = true;
	}
	return res;
}

void main()
{
	KeyType ar[] = { 53, 17, 78, 9, 45, 65, 87, 23, 81, 94, 88, 17, 100 };
	int n = sizeof(ar) / sizeof(ar[0]);
	BSTree root = NULL;
	for (int i = 0; i<n; ++i)
	{
		cout << Insert(&root, ar[i]) << " ";
	}
	cout << endl;
	InOrder(root);
	cout << endl;
	NiceInOrder(root);
	cout << endl;
	NiceInOrder2(root);
	cout << endl;

	//删除
	cout << "删除了17（左右孩子都不为空）" << endl;
	Remove(root, 17);
	NiceInOrder(root);
	cout << endl << endl;
	cout << "删除了88（左右孩子都为空）" << endl;
	Remove(root, 88);
	NiceInOrder(root);
	cout << endl << endl;
	cout << "删除了45（右孩子都为空）" << endl;
	Remove(root, 45);
	NiceInOrder(root);
	cout << endl << endl;
	cout << "删除了53（根）" << endl;
	Remove(root, 53);
	NiceInOrder(root);
	cout << endl;

	system("pause");
}
