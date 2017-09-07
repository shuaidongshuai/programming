#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct BST
{
	int val;
	BST *left, *right;
	BST(int v = 0) :val(v), left(NULL), right(NULL){}
};

void create(BST *&root,int val)
{
	if (!root)
		root = new BST(val);
	else if (val < root->val)
		create(root->left, val);
	else if (val > root->val)
		create(root->right, val);
}
BST *create(string s)
{
	BST *root = NULL;
	int len = s.length();
	int num = 0;
	for (int i = 0; i < len + 1; ++i)//这里注意一下len + 1，不然最后一个数就没了
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			num = 10 * num + s[i] - '0';
			continue;
		}
		else if (s[i] == ' ' || s[i] == 0)
		{
			create(root, num);
			num = 0;
		}
	}
	return root;
}
void printPre(BST *root)
{
	if (root)
	{
		cout << root->val << " ";
		printPre(root->left);
		printPre(root->right);
	}
}
void printMid(BST *root)
{
	if (root)
	{
		printMid(root->left);
		cout << root->val << " ";
		printMid(root->right);
	}
}
void printPost(BST *root)
{
	if (root)
	{
		printPost(root->left);
		printPost(root->right);
		cout << root->val << " ";
	}
}
int main()
{
	string s;
	int n;
	BST *root;
	while (cin >> n)//题目本来要输入一个n，代表数字个数，由于我的create函数可以完全识别数字个数，所以这个n在这个程序中毫无意义
	{
		getchar();//接收回车符
		getline(cin, s);//读取一行
		root = create(s);
		printPre(root);
		cout << endl;
		printMid(root);
		cout << endl;
		printPost(root);
		cout << endl;
	}
	return 0;
}
/*
88
35 7 35 25 42 90 88 7 21 86 79 85 38 85 66 93 11 28 60 37 7 86 31 76 38 58 6 85 94 61 76 98 92 69 24 100 26 63 72 98 51 21 93 38 65 41 46 9 58 36 77 51 62 92 1 28 84 45 88 10 75 31 83 51 6 13 8 66 18 88 34 61 59 92 30 36 92 14 43 2 37 78 72 63 43 46 13 35
*/
int main2()
{
	//string str;
	//getline(cin, str);
	char str[100];
	gets(str);
	cout << str << endl;
	return 0;
}