#include<iostream>
#include <vld.h>
#include <queue>
using namespace std;

#define M 5  //奇数
#define MAXNUM (M-1)
#define MINNUM (M/2)
#define KeyType char

class BNode;

typedef struct
{
	BNode *pnode;
	int index;
	bool tag;
}Result;

typedef struct{} Record;

typedef struct
{
	KeyType key;
	Record *recptr;
}ElemType;

class BNode
{
public:
	BNode(ElemType et)
	{
		data[1] = et;
		num = 1;
		parent = NULL;
		for (int i = 0; i <= M; i++)
			sub[i] = NULL;
	}
	BNode(BNode *left, int first, int end)
	{
		num = end - first + 1;
		parent = NULL;
		/*改sub*/
		for (int i = 0; i <= num; i++)
		{
			sub[i] = NULL;
			if (left->sub[first - 1 + i])
			{
				sub[i] = left->sub[first - 1 + i];
				left->sub[first - 1 + i]->parent = this;
			}
		}
		for (int i = 1; i <= num; i++)
			data[i] = left->data[first++];
	}
	~BNode(){}
public:
	int num;
	BNode *parent;
	ElemType data[M + 1];
	BNode *sub[M + 1];
};
class BTree
{
private:
	BNode *root;
public:
	BTree() :root(NULL){}
	Result findValue(KeyType kx)
	{
		////////////////////////////////////LaoYang Programing////////////////////////////////////////////////
		Result res = { NULL, -1, false };
		BNode *ptr = root;
		while (ptr)
		{
			ptr->data[0].key = kx;
			int i = ptr->num;
			while (kx < ptr->data[i].key)
				--i;
			res.pnode = ptr;
			res.index = i;
			if (i > 0 && ptr->data[i].key == kx)
			{
				res.tag = true;
				break;
			}
			ptr = ptr->sub[i];
		}
		return res;
	}
	Result SearchValue(BNode *ptr, KeyType kx)
	{
		Result res = { NULL, -1, false };
		if (ptr != NULL)
		{
			ptr->data[0].key = kx;
			int i = ptr->num;
			while (kx < ptr->data[i].key)
				i--;
			res.index = i;
			res.pnode = ptr;
			if (i > 0 && ptr->data[i].key == kx)
				res.tag = true;
			else if (ptr->sub[i])
				res = SearchValue(ptr->sub[i], kx);
		}
		return res;
	}
	bool Insert(ElemType et)
	{
		if (root == NULL)
		{
			root = new BNode(et);
			return true;
		}
		//Result res = SearchValue(root, et.key); 
		Result res = findValue(et.key);
		if (res.tag)
			return false;
		BNode *pa = res.pnode;
		//把数据插入到node中
		insert_data(pa, et);

		if (pa->num == M)//如果已经满了
			split(pa);//要分裂
		return true;
	}
	void split(BNode *node)
	{
		if (node)
		{
			//改变原节点
			node->num = 2;
			//创建右节点
			BNode *right = new BNode(node, M / 2 + 2, M);

			BNode *pa = node->parent;
			/*分裂到了root*/
			if (!pa)
			{
				BNode *newRoot = new BNode(node->data[M / 2 + 1]);
				newRoot->sub[0] = node;
				newRoot->sub[1] = right;
				node->parent = newRoot;
				right->parent = newRoot;
				node->num = M / 2;
				root = newRoot;
			}
			else //没有分裂到root
			{
				//把et插入到父节点数据域中
				int index = insert_data(pa, node->data[3]);
				pa->sub[index] = right;
				right->parent = pa;
				//判断是否需要向上继续分裂
				if (pa->num > MAXNUM)
					split(pa);
			}
		}
	}
	int insert_data(BNode *node, ElemType et)
	{
		int i = node->num;
		while (node->data[i].key > et.key && i > 0)
		{
			node->data[i + 1] = node->data[i];
			node->sub[i + 1] = node->sub[i];
			i--;
		}
		node->data[i + 1] = et;
		node->sub[i + 1] = NULL;
		node->num++;
		return i + 1;
	}
	void InOrder(BNode *ptr)
	{
		if (ptr)
		{
			InOrder(ptr->sub[0]);
			for (int i = 1; i <= ptr->num; i++)
			{
				cout << ptr->data[i].key << "  ";
				InOrder(ptr->sub[i]);
			}
		}
	}
	void InOrder()
	{
		InOrder(root);
	}
	void layer_print()
	{
		queue<BNode*> q;
		BNode* node;
		if (!root)
		{
			cout << "没有节点了" << endl;
			return;
		}
		q.push(root);
		while (!q.empty())
		{
			node = q.front();
			q.pop();
			for (int i = 0; i <= node->num; i++)
			{
				if (node->sub[i])
					q.push(node->sub[i]);
			}
			for (int i = 1; i <= node->num; i++)
				cout << node->data[i].key << "  ";
			cout << endl;
		}
	}
	//////////////////////////////删除//////////////////////////////////////////////
	bool Remove(ElemType et)
	{
		if (!root) return false;

		Result res = findValue(et.key);
		BNode *node = res.pnode;
		BNode *pre = FindPrev(node, res.index);
		BNode *next = FindNext(node, res.index);
		BNode *adjNode = remove_key(node,pre,next,res.index,et.key);

		if (adjNode->parent && adjNode->num < MINNUM)
			Adjust_Leaf(adjNode);
		else if (!adjNode->parent && !adjNode->num)
		{
			delete root;
			root = NULL;
		}
	}
	void remove_key_pre(BNode *node, BNode *pre, int index, KeyType k)
	{
		node->data[index] = pre->data[pre->num];
		pre->num--;
	}
	void remove_key_next(BNode *node, BNode *next, int index, KeyType k)
	{
		node->data[index] = next->data[1];
		for (int i = 1; i < next->num; i++)
			next->data[i] = next->data[i + 1];
		next->num--;
	}
	BNode* remove_key(BNode *node, BNode *pre, BNode *next, int index, KeyType k)
	{
		if (pre && pre->num > MINNUM)
		{
			remove_key_pre(node, pre, index, k);
			return pre;
		}
		else if (next && next->num > MINNUM)
		{
			remove_key_next(node, next, index, k);
			return next;
		}
		else if (pre)
		{
			remove_key_pre(node, pre, index, k);
			return pre;
		}
		else if (next)
		{
			remove_key_next(node, next, index, k);
			return next;
		}
		else
		{
			//叶节点
			while (index != node->num)
			{
				node->data[index] = node->data[index + 1];
				index++;
			}
			node->num--;
			return node;
		}
	}
	BNode *FindPrev(BNode *ptr,int index)
	{
		if (ptr = ptr->sub[index - 1])
		{
			while (ptr->sub[ptr->num])
				ptr = ptr->sub[ptr->num];
			return ptr;
		}
		return NULL;
	}
	BNode *FindNext(BNode *ptr, int index)
	{
		if (ptr = ptr->sub[index])
		{
			while (ptr->sub[0])
				ptr = ptr->sub[0];
			return ptr;
		}
		return NULL;
	}
	void borrow_left(BNode *node, BNode *left,BNode *pa,int index)
	{
		node->data[0] = pa->data[index];
		pa->data[index] = left->data[left->num];
		for (int i = node->num; i >= 0; i--)
		{
			node->data[i + 1] = node->data[i];
			node->sub[i + 1] = node->sub[i];
		}
		node->sub[0] = left->sub[left->num];
		if (left->sub[left->num])
			left->sub[left->num]->parent = node;
		
		node->num++;
		left->num--;
	}
	void borrow_right(BNode *node, BNode *right, BNode *pa, int index)
	{
		node->data[node->num + 1] = pa->data[index];
		pa->data[index] = right->data[0];
		node->sub[node->num + 1] = right->sub[0];
		if (right->sub[0])
			right->sub[0]->parent = node;
		for (int i = 1; i < right->num; i++)
			right->data[i] = right->data[i + 1];
		for (int i = 0; i < right->num; i++)
			right->sub[i] = right->sub[i + 1];

		node->num++;
		right->num--;
	}
	void mergeNode(BNode *left,BNode *right,BNode* pa, int index)
	{
		if (!left)
			left = new BNode(pa->data[index + 1]);
		else
			left->data[++left->num] = pa->data[index + 1];
		int num = left->num;
		if (right)
		{
			//调整left兄弟
			for (int i = 1; i <= right->num; i++)
				left->data[num + i] = right->data[i];
			for (int i = 0; i <= right->num; i++)
			{
				left->sub[num + i] = right->sub[i];
				if (right->sub[i])
					right->sub[i]->parent = left;
			}
			left->num += right->num;
		}
		//调整父节点
		if (pa->num == 1)
		{
			//这时候要换根节点
			left->parent = NULL;
			root = left;
			//不能在里面删除当前root
			//delete pa;
			//pa = NULL;
			pa->num = -1;//标记
		}
		else
		{
			for (int i = index + 1; i < pa->num; i++)
			{
				pa->data[i] = pa->data[i + 1];
				pa->sub[i] = pa->sub[i + 1];
			}
			pa->num--;
		}
		delete right;
	}
	void Adjust_Leaf(BNode *node)
	{
		BNode *leftBro = NULL, *rightBro = NULL, *parent = NULL;
		parent = node->parent;
		//找出node在父节点中的index
		int index = find_index(node,parent);

		if (index - 1 >= 0)
			leftBro = parent->sub[index - 1];
		if (index + 1 <= node->num)
			rightBro = parent->sub[index + 1];

		if (index - 1 < 0)
		{
			//没有左兄弟   向右借
			if (rightBro->num > MINNUM)
				borrow_right(node, rightBro, parent, index);
			//右兄弟没钱，和右兄弟合并
			else
				mergeNode(node, rightBro, parent, index);
		}
		else if (index + 1 <= MAXNUM)
		{
			//没有右兄弟   向左借
			if (leftBro->num > MINNUM)
				borrow_left(node, leftBro, parent, index);
			//左兄弟没钱，和左兄弟合并
			else
				mergeNode(leftBro, node, parent, index - 1);
		}
		else
		{
			//有两兄弟,优先向左借
			if (leftBro->num > MINNUM)
				borrow_left(node, leftBro, parent, index);
			else if (rightBro->num > MINNUM)
				borrow_right(node, rightBro, parent, index);
			else
				mergeNode(leftBro, node, parent, index);
		}
		if (parent->num == -1)
		{
			delete parent;
			parent = NULL;
			return;
		}
		if (parent->num < MINNUM && parent->parent)
			Adjust_Leaf(parent);
	}
	//找出ptr在父节点中的index
	int find_index(BNode *ptr, BNode *pa)
	{
		KeyType min = ptr->data[1].key;
		int i;
		for (i = 1; i <= pa->num; i++)
		{
			if (min < pa->data[i].key)
			{
				return i - 1;
			}
		}
		return i - 1;
	}
};

int main()
{
	KeyType ar[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
	int n = sizeof(ar) / sizeof(ar[0]) - 1;
	ElemType item;
	BTree root;
	for (int i = 0; i < n; i++)
	{
		item.key = ar[i];
		item.recptr = NULL;
		root.Insert(item);
		root.InOrder();
		/*cout << "★★" << endl;
		root.layer_print();*/
		cout << endl << "------------------------------------添加--------------------------------------" << ar[i] << endl;
	}
	for (int i = 0; i < n; i++)
	{
		item.key = ar[i];
		item.recptr = NULL;
		root.Remove(item);
		root.InOrder();
		/*cout << "★★" << endl;
		root.layer_print();*/
		cout << endl << "------------------------------------删除--------------------------------------" << ar[i] << endl;
	}
	system("pause");
}
