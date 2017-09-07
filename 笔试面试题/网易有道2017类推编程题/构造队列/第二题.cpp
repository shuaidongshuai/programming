#include <iostream>
using namespace std;
/*
思路：发现的规律，从 1---n  只要每次给第二个位置依次赋值就可以得到原来的数列
1---n  看做是一个循环链表，每当我们访问到“第二个”没有被赋值的元素。我们就可以进行 1---n  的依次赋值
当我们访问到最后一个元素，记得要跳到第一个元素，一直遍历这个数组。
*/
void sort(int* arr, int n)
{
	int i = 0, j = 1;
	int yes = 0;
	while (1)
	{
		if (arr[i] == 0)
		{
			if (j == n)			//跳出循环的条件，只有找到最后一个未被赋值的元素，赋值之后我们，我们才跳出循环
			{
				arr[i] = j;
				break;
			}
			if (yes == 1)
			{
				arr[i] = j++;
				yes = -1;
			}
			yes++;

		}
		if (++i == n)
			i = 0;
	}
}

int main()
{
	int m, n, j;
	cin >> m;
	int* arr;
	for (int i = 0; i < m; i++)
	{
		cin >> n;
		arr = new int[n]();
		sort(arr, n);
		for (j = 0; j< n - 1; j++)
		{
			cout << arr[j] << " ";
		}
		cout << arr[j] << endl;
		delete arr;
	}

	system("pause");
	return 0;
}
