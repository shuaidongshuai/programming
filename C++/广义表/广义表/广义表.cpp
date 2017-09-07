#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include<malloc.h>
#include<string.h>

typedef enum{ HEAD = 0, INT = 1, CHAR = 2, LIST = 3 } NodeType;

struct GenNode;
typedef	union
{
	int ref;
	int intinfo;
	char chinfo;
	GenNode *hlink;
}ElemType;

struct GenNode
{
	NodeType utype; // HEAD INT CHAR LIST
	ElemType value;
	GenNode *tlink;
};

class GenList
{
private:
	GenNode *first;
	static GenNode * _Buynode()
	{
		GenNode *s = (GenNode*)malloc(sizeof(GenNode));
		if (NULL == s) exit(1);
		memset(s, 0, sizeof(GenNode));
		return s;
	}

	static GenNode * _BuyHead(int ref)
	{
		GenNode *s = _Buynode();
		s->utype = HEAD;
		s->value.ref = ref;
		return s;
	}
	static GenNode * _BuyInt(int x)
	{
		GenNode *s = _Buynode();
		s->utype = INT;
		s->value.intinfo = x;
		return s;
	}
	static GenNode * _BuyChar(char x)
	{
		GenNode *s = _Buynode();
		s->utype = CHAR;
		s->value.chinfo = x;
		return s;
	}
	static GenNode * _BuyList(GenNode *hlink)
	{
		GenNode *s = _Buynode();
		s->utype = LIST;
		s->value.hlink = hlink;
		return s;
	}
	static void _Freenode(GenNode *p)
	{
		free(p);
	}


public:
	GenList() :first(NULL) {}// str=>"";
	static void Del_String_LR_Parentheses(char *sub, char *str)
	{
		int n = strlen(str);
		strncpy(sub, str + 1, n - 2);
		sub[n - 2] = '\0';
	}
	static bool sever(char *hsub, char *sub)
	{// sub = 12,'a',(23,'b',(34,'c','x'),100
		//      0 1 2 3 4 5 6
		int n = strlen(sub);
		int i = 0;
		if (sub[i] != '(')
		{
			while (i<n && sub[i] != ',')
			{
				++i;
			}
		}
		else
		{
			int count = 0;
			while (++i < n && sub[i] != ')' || count)
			{
				if (sub[i] == '(')
					count++;
				else if (sub[i] == ')')
					count--;
			}
			i++;
		}
		if (i == n)
		{
			strcpy(hsub, sub);
			sub[0] = '\0';
		}
		else
		{
			strncpy(hsub, sub, i);
			hsub[i] = '\0';
			strcpy(sub, sub + i + 1);
		}
		return true;
	}
	//用于判断这个字符串是整数，还是字符，还是下一个表，对应返回1,2,3
	static int judge(char *str)
	{
		if (*str > '0' && *str <= '9')
			return 1;
		else if (*str == '\'')
			return 2;
		else if (*str == '(')
			return 3;
		return -1;
	}
	//把 'a' -> a
	static char string_to_char(char *str)
	{
		return *(str + 1);
	}

	static GenNode * Create(char *str)
	{
		GenNode *s = _BuyHead(1);
		if (strlen(str) > 0 && strcmp(str, "()") != 0)
		{
			GenNode *p = s;
			int len = strlen(str) + 1;
			char * sub = new char[len];
			char *hsub = new char[len];
			Del_String_LR_Parentheses(sub, str);
			while (strlen(sub) > 0)
			{
				if (!sever(hsub, sub))
				{
					exit(1);
				}
				GenNode *node = NULL;
				if (judge(hsub) == 1)
				{
					int a = atoi(hsub);
					node = _BuyInt(a);
					p->tlink = node;
				}
				else if (judge(hsub) == 2)
				{
					char a = string_to_char(hsub);
					node = _BuyChar(a);
					p->tlink = node;
				}
				else if (judge(hsub) == 3)
				{
					node = Create(hsub);
					node = _BuyList(node);
					p->tlink = node;
				}
				p = node;
			}
			delete[]sub;
			delete[]hsub;
		}
		return s;
	}
	char *str;//为拷贝而定义的，偷懒行为
	void copy(GenList *&list)
	{
		list->CreateGenList(str);
	}
	void CreateGenList(char *str)
	{
		if (str != NULL)
		{
			int len = strlen(str);
			this->str = new char[len + 1];
			strcpy(this->str, str);
			first = Create(str);
		}
	}
	void printList(GenNode* node)
	{
		node = node->tlink;
		while (node != NULL)
		{
			if (node->utype == INT)
			{
				cout << node->value.intinfo << "\t";
			}
			else if (node->utype == CHAR)
			{
				cout << node->value.chinfo << "\t";
			}
			else if (node->utype == LIST)
			{
				printList(node->value.hlink);
			}
			node = node->tlink;
		}
	}
	void Print()
	{
		printList(first);
		cout << endl;
	}
	static int Depth(GenNode *ptr)
	{
		int max = 0;
		ptr = ptr->tlink;
		while (ptr != NULL)
		{
			if (ptr->utype == LIST)
			{
				int depth = Depth(ptr->value.hlink);
				max = depth > max ?  depth: max;
			}
			ptr = ptr->tlink;
		}
		return max + 1;
	}
	int Depth() const
	{
		int n = 0;
		if (first != NULL)
		{
			n = Depth(first);
		}
		return n;
	}
};

void main()
{
	GenList gen;
	char *str1 = "()";
	char *str2 = "(12,'a')";
	char *str3 = "(12,'a',(23,'b',(34,'c'),'x'),100)";
	gen.CreateGenList(str3);
	gen.Print();
	cout << gen.Depth() << endl;

	GenList *gen2 = new GenList;
	gen.copy(gen2);
	gen.Print();


	getchar();
}