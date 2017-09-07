#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define MAX 100000

typedef struct {
	int parent;
	int lchild;
	int rchild;
	int weight;//权值
	char value;//需要编的字符
	char* code;//编码后的二进制
}HuffmanNode;

typedef struct{
	char* code;
	int len;
}Hcode;

//创建haffman树
void  huffmanTree(HuffmanNode Node[], int n)
{
	int m1, m2;//两个最小权值点
	int x1, x2;//计算最小权值点时，记录该节点在数组中的序号 
	//初始化整个树
	for (int i = 0; i< 2 * n - 1; i++)
	{
		Node[i].parent = -1;
		Node[i].lchild = -1;
		Node[i].rchild = -1;
		Node[i].weight = 0;//权值	
	}
	//输入n个叶子节点的权值
	for (int i = 0; i<n; i++)
	{
		cout << "值: and 频率:" << endl;
		cin >> Node[i].value >> Node[i].weight;
	}
	//构建树
	for (int i = 0; i < n - 1; i++)//两个节点变成一个节点，最后要剩余一个节点，所以是 n - 1
	{
		m1 = m2 = MAX;//给最小权值初始化一个很大的数
		x1 = x2 = 0;
		for (int j = 0; j<n + i; j++)
		{
			if (Node[j].weight < m1 && Node[j].parent == -1)//出现了最小权值的情况
			{
				m2 = m1;
				m1 = Node[j].weight;
				x2 = x1;
				x1 = j;//记录当前最小权值的Node 在数组中的序号
			}
			else if (Node[j].weight < m2 && Node[j].parent == -1)//出现第二小权值的情况
			{
				m2 = Node[j].weight;
				x2 = j;
			}
		}
		Node[n + i].weight = Node[x1].weight + Node[x2].weight;
		Node[n + i].lchild = x1;
		Node[n + i].rchild = x2;
		//改变子节点的parent 为当前创建的节点
		Node[x1].parent = n + i;
		Node[x2].parent = n + i;
	}
}

//根据权值进行编码
void codeHuffman(HuffmanNode* node, int n)
{
	Hcode tempCode;
	int parent, child;
	tempCode.code = new char[n];
	for (int i = 0; i < n; i++)
	{
		tempCode.len = n;
		parent = node[i].parent;
		child = i;
		while (parent != -1)//没有父类就跳出循环
		{
			// 若当前节点是父节点的左孩子，则编码为0
			if (node[parent].lchild == child)
				tempCode.code[--tempCode.len] = '0';
			else if (node[parent].rchild == child)
				tempCode.code[--tempCode.len] = '1';
			child = parent;
			parent = node[parent].parent;
		}
		int len = n - tempCode.len;
		node[i].code = new char[len + 1];
		memcpy(node[i].code, tempCode.code + tempCode.len, len);
		node[i].code[len] = '\0';
	}
	delete[] tempCode.code;
}

char* getcodeHuffman(HuffmanNode* node, char* code, int n)
{
	char* buf = new char[1024];
	memset(buf, 0, sizeof(buf));
	char* c = code;
	while (*c != '\0')
	{
		for (int i = 0; i < n; i++)
		{
			if (node[i].value == *c)
			{
				strcat(buf, node[i].code);
			}
		}
		c++;
	}
	return buf;
}

void decodeHuffman(HuffmanNode* node, char *code, int n)
{
	int curt = 2 * n - 2;
	int i;
	char *c = code;
	while (*c != '\0')
	{
		for (i = curt; node[i].lchild != -1 && node[i].rchild != -1; )
		{
			if (*c == '0')
				i = node[i].lchild;
			else if (*c == '1')
				i = node[i].rchild;
			c++;
		}
		cout << node[i].value;
	}
	cout << endl;
}

void print(HuffmanNode* node, int n)
{
	for (int i = 0; i < n; i++)
		cout << node[i].value << "\t编码：" << node[i].code << endl;
}
int main()
{
	int n;
	char* code = "11101100111110010";	//解码
	char* code2 = "acebdf";				//编码
	while (1)
	{
		cout << "要创建几个节点" << endl;
		cin >> n;
		HuffmanNode* Node = new HuffmanNode[2 * n - 1];
		huffmanTree(Node, n);
		codeHuffman(Node, n);
		print(Node, n);

		char * buf = getcodeHuffman(Node, code2, n);
		cout << "acebdf\t\t\t编码后得到\t " << buf << endl;
		cout << "11101100111110010\t解码后得到\t";
		decodeHuffman(Node, code, n);
	}
	system("pause");
}
/*
6
a 1
b 2
c 3
d 4
e 5
f 6
----------------------------------------------------------------
a       编码：1110
b       编码：1111
c       编码：110
d       编码：00
e       编码：01
f       编码：10
acebdf                  编码后得到       11101100111110010
11101100111110010       解码后得到      acebdf



*/