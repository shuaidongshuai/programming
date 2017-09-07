#include <iostream>
using namespace std;

/*建立的是最小堆*/
/*下面arr[i]代表当前元素，arr[j]代表父，或，子*/
/*堆的插入*/
void insert(int *arr,int i)
{
	int j = (i - 1) / 2;//父节点下标
	int temp = arr[i];//需要插入的点
	while (j >= 0 && i > 0)//父节点肯定是>=0的，当前节点肯定也是>0的 ▲▲▲ i>0不能省，不然会出现i=j=0死循环
	{
		if (temp > arr[j])//当前节点比父节点大
			break;

		/*说明子比父小，需要移动*/
		arr[i] = arr[j];//父节点下来
		i = j;
		j = (i - 1) / 2;
	}
	arr[i] = temp;
}
/*头结点下沉*/
void heapFixdown(int *arr, int i, int n)
{
	int j = 2 * i + 1;//左边的子节点
	int temp = arr[i];
	while (j < n)//他的子节点要小于n					我写错了： i<n 导致了数组越界  子节点肯定比它大
	{
		if (j + 1 < n && arr[j + 1] < arr[j]) //在左右孩子中找最小的(如果右孩子更小，那么取右孩子)
			j++;
		if (temp < arr[j])
			break;
		arr[i] = arr[j];
		i = j;
		j = 2 * i + 1;
	}
	arr[i] = temp;
}

void swap(int &a, int &b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

/*最小堆排序*/
/*一般得到的都是递减数列*/
void SortDown(int *arr, int n)
{
	/*全部插入，可以得到一个最小的数*/
	for (int i = 0; i < n; i++)
		insert(arr, i);
	/*每次都交换顶层元素，每次都能得到当前最小堆的最小元素，最后得到的数据是 从大到小 排列的*/
	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[i], arr[0]);
		heapFixdown(arr, 0, i);
	}
}

/*★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
										以下内容可以不看，都是测试
★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★*/


/*也可以的到“递增数列”，不过传进来的数组必须是引用，因为发生copy,不要以为传指针就没事，指针也要发生拷贝，
平时我们改的是指针指向的内容，所以觉得传指针就能改变值，其实我们没有改变指针本身，如果要改变指针本身的指向，必须加上引用*/
void SortUp(int *&arr, int n)
{
	int *a = new int[n];

	for (int i = 0; i < n; i++)
		insert(arr, i);

	for (int i = 1; i < n; i++)
	{
		a[i - 1] = arr[0];
		arr[0] = arr[n - i];
		heapFixdown(arr, 0, n - i);
	}
	a[n - 1] = arr[0];
	arr = a;						//图方便，直接改变指针指向的地址，平时我们没有改变地址，都只是改变地址上的内容罢了
}

void test1()
{
	int arr[] = { 5, 8, 1, 6, 3, 4, 2, 9, 7 };

	SortDown(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << "\t";
		if (i == 0 || i == 2 || i == 6)
			cout << endl;
	}
	cout << endl;
}

void test2()
{
	int *arr = new int[9]{ 5, 8, 1, 6, 3, 4, 2, 9, 7 };//因为要改地址，所以这里还不能用数组

	SortUp(arr,9);

	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << "\t";
		if (i == 0 || i == 2 || i == 6)
			cout << endl;
	}
	cout << endl;
}

int main()
{
	test1();
	cout << "------------------------------" << endl;
	test2();

	getchar();
}