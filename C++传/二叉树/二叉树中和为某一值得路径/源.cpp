#include <iostream>
#include <vector>
using namespace std;


typedef struct NODE{
	char val;
	struct NODE *left, *right;
}Node, *Tree;

Node *Create(char *&str)
{
	if (!str || !*str || '#' == *str)
		return NULL;
	Node *node = new Node;
	node->val = *str;
	node->left = Create(++str);
	node->right = Create(++str);
	return node;
}
//加vector的目的就在于如果遍历到了cur == exp 那么就可以直接打印了
void FindPath(Node *node, vector<char> &v, char exp, char cur)
{
	cur += node->val - '0';
	v.push_back(node->val);
	//如果当前节点是叶节点
	if (!node->left && !node->right && cur == exp)
	{
		for (vector<char>::iterator it = v.begin(); it != v.end(); it++)
			cout << *it << " ";
		cout << endl;
	}
	//如果不是叶节点，遍历他的子节点
	if (node->left)
		FindPath(node->left, v, exp, cur);
	if (node->right)
		FindPath(node->right, v, exp, cur);
	//如果都没找到，说明当前节点下面没有合适的路径  如果上面不用引用，那么下面就可以不要
	v.pop_back();
}
void FindPath(Node *node, char expect)
{
	if (!node)
		return;
	vector<char> v;
	FindPath(node, v, expect, '0');
}

void print(Node *node)
{
	if (node)
	{
		cout << node->val << " ";
		print(node->left);
		print(node->right);
	}
}
int main()
{

	char *str1 = "123##4##2324##1###6##";
	Node *node1 = Create(str1);
	print(node1);
	cout << endl << "--------------------------" << endl;
	FindPath(node1, '9');
	system("pause");
}