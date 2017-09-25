#include <iostream> 
#include <stack>
using namespace std;

/**把数组分为两部分，轴 axis 左边的部分都小于轴右边的部分**/
int SplitByMid(int *arr, int l, int r)
{
	if(l > r)
		return 0;
	int axis = arr[l];
	while(l < r){
		while(l < r && arr[r] > axis)
			--r;
		arr[l] = arr[r];
		while(l < r && arr[l] <= axis)
			++l;
		arr[r] = arr[l];
	}
	arr[l] = axis;
	return l;
}
/* 递归 */
int QuickSort0(int *arr, int l, int r)
{
	if(l < r){
		int mid = SplitByMid(arr, l, r);
		QuickSort0(arr, l, mid - 1);
		QuickSort0(arr, mid + 1, r);
	}
}
/* 非递归 */
class HeadTail
{
public:
	int left;
	int right;
	HeadTail(int l, int r):left(l),right(r){}
};
int QuickSort(int *arr, int l, int r)
{
	if(l >= r)
		return 0;
	stack<HeadTail *> s;//把需要再次遍历的头尾角标放入栈中 
	int mid;
	s.push(new HeadTail(l, r));
	while(!s.empty()){
		HeadTail *ht = s.top();
		s.pop();
		l = ht->left;
		r = ht->right;
		delete ht;
		mid = SplitByMid(arr, l, r);
		if(l < mid - 1)
			s.push(new HeadTail(l, mid - 1));
		if(mid + 1 < r)
			s.push(new HeadTail(mid + 1, r));
	}
	return 1;
}

void print(int *arr,int n)
{
	for(int i = 0;i < n;i++)
		cout<<*arr++<<" ";
	cout<<endl;
}
int main()
{
	int arr[] = {4,5,6,4,1,9,2,3,7,8,11,0,34,65,76,3,34,435,234,543,6,3214,32,4,34};
	int size = sizeof(arr)/sizeof(arr[0]);
//	QuickSort0(arr,0,size - 1);
	QuickSort(arr,0,size - 1);	
	print(arr,size);
}
