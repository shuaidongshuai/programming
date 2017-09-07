#include <iostream>
#include <cstring>
#include <assert.h>
#include <List>
using namespace std;

template<class T>
class Node
{
public:
	Node *next;
	T val;
	Node(Node *n = NULL, T v = 0) :next(n), val(v){}
};
//我这个hash允许有相同的值 
template<class T>
class Hash
{
public:
	Node<T> **hashTable;
	int hashLen;
	int num;
public:
	Hash(int len)
	{
		hashTable = new Node<T>*;
		for (int i = 0; i < len;i++)
			hashTable[i] = new Node<T>;
		hashLen = len;
	}
	//插入hash表中
	int InsertHash(T data)
	{
		int addr = data % hashLen;
		Node<T> *head = hashTable[addr];
		//解决冲突
		if (head)
		{
			Node<T> *newNode = new Node<T>(NULL, data);
			newNode->next = head->next;
			head->next = newNode;
		}
		else
			head->val = data;
		num++;
		return addr;
	}
	//找值 
	Node<T> *FindInHashTable(T data)
	{
		int addr = data % hashLen;
		Node<T> *first = hashTable[addr];
		while (first && first->val != data)
			first = first->next;
		return first;
	}
	//删除
	bool Remove(T data)
	{
		int addr = data % hashLen;
		Node<T> *pre = NULL;
		Node<T> *first = hashTable[addr];
		if (first->val == data)
		{
			Node<T> *node = hashTable[addr]->next;
			delete hashTable[addr];
			hashTable[addr] = node;
		}
		else
		{
			Node<T> *pre = first;
			while (first && first->val != data)
			{
				pre = first;
				first = first->next;
			}
			if (!first)
				return false;
			pre->next = first->next;
			delete first;
			return true;
		}
	}
};


int main()
{
	Hash<int> *h = new Hash<int>(5);
	int arr[] = { 1, 11, 3, 21,91, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i<n; i++)
		cout << h->InsertHash(arr[i]) << endl;
	for (int i = 0; i<n; i++)
		cout << h->Remove(arr[i]) << " ";
	system("pause");
}

