#include "Tree.h"

/*Morris遍历时间复杂度为O(n)空间复杂度为O(1)*/
//中序
void MidMorris(Node *root){
	if (!root)
		return;
	Node *cur = root, *pre = NULL;
	while (cur){
		if (!cur->left){
			cout << cur->val << "   ";
			cur = cur->right;
		}
		else{//有左孩子肯定有前驱节点指向自己
			pre = cur->left;
			while (pre->right && pre->right != cur)//!=cur是因为之前可以已经指向了cur
				pre = pre->right;
			if (!pre->right){//说明有前驱节点
				pre->right = cur;
				cur = cur->left;
			}
			else{
				cout << cur->val << "   ";//说明就是前驱节点通过->right找到的cur
				pre->right = NULL;//恢复原样
				cur = cur->right;
			}
		}
	}
	cout << endl;
}
//先序
void PreMorris(Node *root){
	if (!root)
		return;
	Node *cur = root, *pre = NULL;
	while (cur){
		if (!cur->left){
			cout << cur->val << "   ";
			cur = cur->right;
		}
		else{
			pre = cur->left;
			while (pre->right && pre->right != cur)
				pre = pre->right;
			if (!pre->right){
				cout << cur->val << "   ";//change------
				pre->right = cur;
				cur = cur->left;
			}
			else{
				pre->right = NULL;
				cur = cur->right;
			}
		}
	}
	cout << endl;
}
/*
后续遍历稍显复杂，需要建立一个临时节点dump，令其左孩子是root。
并且还需要一个子过程，就是倒序输出某两个节点之间路径上的各个节点。
*/
//相当于链表逆序打印---1  时间复杂度为O(N^2)
void printReverse(Node* from, Node *to) {
	if (!from || !to)
		return;
	Node *start = from, *end = to, *pre = from;
	while (start != end){
		while (start != end){
			pre = start;
			start = start->right;
		}
		cout << start->val << "   ";
		end = pre;
		start = from;
	}
	cout << from->val << "   ";
}
//修改指针指向---2  时间复杂度为O(N)
void Reverse(Node *from, Node *to){
	if (!from || !to)
		return;
	Node *pre = from, *cur = pre->right, *next;
	while (cur && pre != to){//避免为空 因为是用pre判断的
		next = cur->right;
		cur->right = pre;
		pre = cur;
		cur = next;
	}
}
void printReverse2(Node* from, Node *to) {
	if (!from || !to)
		return;
	Reverse(from, to);//本来是from 指向 to的链  change to 指向from的链
	Node *p = to;
	while (p != from){
		cout << p->val << "   ";
		p = p->right;
	}
	cout << p->val << "   ";
	Reverse(to, from);
}
void PostMorris(Node *root) {
	Node dump(0);//循环结束的条件
	dump.left = root;
	Node *cur = &dump, *prev = NULL;
	while (cur) {
		if (cur->left == NULL) {
			cur = cur->right;
		}
		else {
			prev = cur->left;
			while (prev->right != NULL && prev->right != cur)
				prev = prev->right;

			if (prev->right == NULL) {
				prev->right = cur;
				cur = cur->left;
			}
			else {
				printReverse2(cur->left, prev);  // call print
				prev->right = NULL;
				cur = cur->right;
			}
		}
	}
}

int main() {
	char a[] = { '1', '2', '3', ' ', ' ', '4', ' ', ' ', '5', '6' };//注意这里要两个空格，因为左右子树都需要NULL
	int i = 0;
	Tree root = NULL;
	//先创建一棵树
	createTree(root, a, i);
	cout << "递归中序遍历" << endl;
	//递归中序遍历
	inOrderY(root);//3   2   4   1   6   5
	cout << endl << endl << "非递归中序遍历" << endl;
	//非递归中序遍历
	MidMorris(root);//3   2   4   1   6   5

	cout << endl << endl << "递归先序遍历" << endl;
	//递归先序遍历
	preOrderY(root);
	//非递归先序遍历
	cout << endl << endl << "非递归先序遍历" << endl;
	PreMorris(root);

	cout << endl << endl << "递归后序遍历" << endl;
	//递归后序遍历
	postOrderY(root);
	//非递归后序遍历
	cout << endl << endl << "非递归后序遍历" << endl;
	PostMorris(root);

	cin.get();
	return 0;
}