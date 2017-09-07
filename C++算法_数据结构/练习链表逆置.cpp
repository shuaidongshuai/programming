#include <iostream>
#include <cstring>
using namespace std;

//µ¥Á´±íµÄÄæÖÃ
struct LinkNode
{
	char val;
	LinkNode *next;
};

LinkNode *create(char *str)
{
	if (!str)
		return NULL;
	LinkNode *head = new LinkNode;
	head->val = *str++;
	LinkNode *temp = head;
	while (*str)
	{
		LinkNode *node = new LinkNode;
		node->val = *str++;
		temp->next = node;
		temp = temp->next;
	}
	temp->next = NULL;
	return head;
}
//·ÇµÝ¹é 
LinkNode *reverseList(LinkNode *head)
{
	if (!head)
		return NULL;
	LinkNode *pre = NULL, *node = head, *next;
	while (node)
	{
		next = node->next;
		node->next = pre;
		pre = node;
		node = next;
	}
	return pre;
}
//µÝ¹é
LinkNode *resverseList2(LinkNode *pre,LinkNode *node)
{
	LinkNode *head = NULL;
	if(node)
	{
		head = resverseList2(node,node->next);
		node->next = pre;
	}
	else
	{
		head = pre;
	}
	return head;
}
LinkNode *resverseList2(LinkNode *head)
{
	if(!head)
		return NULL;
	return resverseList2(NULL,head);
} 

void print(LinkNode *head)
{
	while (head)
	{
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}
int main()
{
	LinkNode *head = create("abcd");
	print(head);
	LinkNode *reHead = reverseList(head);
	print(reHead);
	LinkNode *reHead2 = reverseList(reHead);
	print(reHead2);
}

