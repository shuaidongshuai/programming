#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;

typedef struct NODE{
	char val;
	struct NODE *left,*right;
	NODE(int val) :val(val), left(NULL), right(NULL){}
}Node, *Tree;

void createTree(Tree &t,char a[],int &i)//注意这里我们必须用&引用，因为我们要改变传进来的root的地址（要为它分配内存）
{
	if (i > 9 || a[i] == ' ')
	{
		t = NULL;
		return;
	}
	cout << a[i] <<"+++"<< endl;

	t = new Node(a[i]);
	createTree(t->left,a,++i);
	createTree(t->right,a,++i);
}
//递归先序遍历
void preOrderY(Tree t)
{
	if (!t)
		return;
	cout << t->val << "   ";
	preOrderY(t->left);
	preOrderY(t->right);
}
//非递归先序遍历

void preOrder(Tree t)
{
	if(!t)
		return;
	stack<Tree> s;
	Tree p = t;
	while(!s.empty() || p)
	{
		if(p)
		{
			cout<<p->val<<"  ";
			s.push(p);
			p = p->left;
		}
		else
		{
			p = s.top();
			s.pop();
			p = p->right;
		}
	}
}
//递归后序遍历
void postOrderY(Tree t)
{
	if (!t)
		return;
	postOrderY(t->left);
	postOrderY(t->right);
	cout << t->val << "   ";
}
//非递归后序遍历
void postOrder(Tree t)
{
	if (!t)
		return;
	Tree p = t;
	Tree pLastVisit = NULL;//pLastVisit:上次访问节点
	stack<Tree> s;
	while(p)
	{
		s.push(p);
		p = p->left;
	}
	while(!s.empty())
	{
		p = s.top();
		s.pop();
		if(!p->right || pLastVisit == p->right)
		{
			cout<<p->val<<"   ";
			pLastVisit = p;
		}
		else
		{
			s.push(p);
			p = p->right;
			while(p)
			{
				s.push(p);
				p = p->left;
			}
		}
	}
}
int main()
{
	char a[] = { '1', '2', '3', ' ', ' ', '4', ' ', ' ', '5', '6' };//注意这里要两个空格，因为左右子树都需要NULL
	int i = 0;
	Tree root = NULL;
	//先创建一棵树
	createTree(root, a, i);
	cout << endl << endl << "递归先序遍历" << endl;
	//递归先序遍历
	preOrderY(root);
	//非递归先序遍历
	cout << endl << endl << "非递归先序遍历" << endl;
	preOrder(root);	
	
	cout << endl << endl << "递归后序遍历" << endl;
	//递归后序遍历
	postOrderY(root);
	//非递归后序遍历
	cout << endl << endl << "非递归后序遍历" << endl;
	postOrder(root);

	cin.get();
	return 0;
}
