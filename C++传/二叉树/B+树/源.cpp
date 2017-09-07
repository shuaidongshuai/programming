#include<iostream>
#include <vld.h>
#include <queue>
using namespace std;

#define M 5  //ÆæÊý
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

class BNode
{
public:
	enum 
	{
		LEAF,
	}utype;
	KeyType k[M + 1];
	int num;
	BNode *pa;
	union
	{
		struct
		{
			BNode *prev, *next;
			Record *recptr[M + 1];
		};
		BNode *sub[M+1];
	};
	Result *FindRoot(BNode *ptr, KeyType kx)
	{
		Result res = { NULL, 1, false };
	}
	Result FindFirst(BNode *ptr, KeyType kx)
	{
		Result res = { NULL, 1, false };
		if (!ptr) return res;
		while (ptr && kx > ptr->k[ptr->num - 1])
			ptr = ptr->next;
		int i = ptr->num - 1;
		while (i >= 0 && kx < ptr->k[i])
			i--;
		res.pnode = ptr;
		res.index = i;
		if (i >= 0 && kx == ptr->k[i])
		{
			res.tag = true;
		}
		else if (i < 0 && ptr->prev)
		{
			res.pnode = ptr->prev;
			res.index = ptr->prev->num - 1;
		}
		
	}
	BNode *Splice_Leaf(BNode *ptr)
	{
		BNode *newNode = new BNode;
		int index = 0;
		for (int i = (M + 1) / 2; i <= M + 1; i++)
		{
			newNode->k[index] = ptr->k[i];
			newNode->sub[index] = ptr->sub[i];
		}
		newNode->pa = ptr->pa;
		newNode->num = (M + 1) / 2;
		ptr->num = (M + 1) / 2;

		BNode* pa = ptr->pa;
		if (pa)
		{
			index = FindIndexFromPa(pa, ptr->k[0]);
		}
	}
	int FindIndexFromPa(BNode *pa, KeyType k)
	{
		int i = pa->num;
		while (i > 0 && pa->k[i] != k)
			i--;
		if (i > 0)
			return i;
		return 0;
	}
	void Insert_Brch_Item(BNode *ptr, int pos, KeyType kx, BNode *right)
	{
		int num = ptr->num;
		for (int i = num; i > pos; i--)
			ptr->k[i + 1] = ptr->k[i];
		for (int i = num; i >= pos; i--)
			ptr->sub[i + 1] = ptr->sub[i];
		ptr->num++;
	}
	BNode *Splice_Brch(BNode *ptr)
	{
		BNode *newNode = new BNode;
	}
};


