#include <iostream>
using namespace std;

class Node
{
public:
	int val;
	Node *next;
	Node(int val) :val(val){ next = NULL; }
};
//注意交换函数：三种交换只能用这种
void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}
Node *SplitByMid(Node *left, Node *right){
	if(!left)
		return left;
	int axis = left->val;//axis为中心
	/* l和r之间的数就是比axis大的数，l指向的是小于等于axis的数 */
	Node *l = left;
	Node *r = l->next;
	while (r != right){
		if (r->val < axis){
			l = l->next;//很重要，先指向下一个再交换（下一个要么是大于axis的，要么就是这个数本身）
			swap(l->val, r->val);
		}
		r = r->next;
	}
	swap(l->val, left->val);//由于是先指向下一个再交换，所以第一个没有被交换 
	return l;
}
void QuickSortList(Node *l, Node *r){
	if (l != r){
		Node *mid = SplitByMid(l, r);
		QuickSortList(l, mid);
		QuickSortList(mid->next, r);//一定要有next不然会死循环
	}
}
void print(Node *head){
	if (head != NULL){
		cout << head->val << " ";
		print(head->next);
	}
}
/* 测试 */
void test1(){
	int arr[] = { 5, 6, 7, 1, 2, 9, 3, 4, 8, 4, 5, 2 };
	int len = sizeof(arr) / sizeof(int);
	Node *head = new Node(arr[0]);
	Node *temp = head;
	for (int i = 1; i < len; ++i){
		Node *n = new Node(arr[i]);
		temp->next = n;
		temp = n;
	}
	print(head);
	cout << endl;
	QuickSortList(head, NULL);
	print(head);
	cout << endl;
} 
void test2(){
	int arr[] = { 5 };
	int len = sizeof(arr) / sizeof(int);
	Node *head = new Node(arr[0]);
	Node *temp = head;
	for (int i = 1; i < len; ++i){
		Node *n = new Node(arr[i]);
		temp->next = n;
		temp = n;
	}
	print(head);
	cout << endl;
	QuickSortList(head, NULL);
	print(head);
} 
int main(){
	test1(); 
	test2();
}
