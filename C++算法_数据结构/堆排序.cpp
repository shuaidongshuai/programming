#include <iostream>
using namespace std;

void swap(int &a, int &b){
	a ^= b;
	b ^= a;
	a ^= b;
}
/* 小根堆 */
//插入
void InsertHeap(int *arr, int i){
	if(!arr || i < 0)
		return;
	int fa = (i - 1) / 2;
	int temp = arr[i];
	while(i > 0){//为啥只判断子节点？ 因为只要i>0，父节点就不可能为负数
		if(temp > arr[fa])
			break;
		arr[i] = arr[fa];
		i = fa;
		fa = (fa - 1) / 2;
	}
	arr[i] = temp;
}
//头结点下沉
void HeadDownHead(int *arr, int n){
	if(!arr || n < 0)
		return;
	int i = 0;//头结点
	int l_child = 2 * i + 1;//左孩子
	int temp = arr[i];
	while(l_child < n){
		//判断左右节点哪个更小
		if(l_child + 1 < n && arr[l_child + 1] < arr[l_child])
			++l_child;//左节点变为右节点
		if(temp < arr[l_child])
			break;
		arr[i] = arr[l_child];
		i = l_child;
		l_child = 2 * l_child + 1;
	}
	arr[i] = temp;
}
//排序
void HeadSort(int *arr, int n){
	if(!arr || n <= 0)
		return;
	//先插入
	for(int i = 0; i < n; ++i)
		InsertHeap(arr,i);
	//然后可以排序了(小根堆  是从大到小排序)
	for(int i = n - 1; i > 0; --i){
		swap(arr[i], arr[0]);
		HeadDownHead(arr,i);
	}
}
///////////////////////测试///////////////////////////////
void test1()
{
	int arr[] = { 5, 8, 1, 6, 3, 4, 2, 9, 7 };

	HeadSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << "\t";
		if (i == 0 || i == 2 || i == 6)
			cout << endl;
	}
	cout << endl;
}
int main(){
	test1();
}
