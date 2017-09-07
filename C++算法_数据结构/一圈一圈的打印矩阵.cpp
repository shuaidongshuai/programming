#include<iostream>
using namespace std;

void printCircle(int **arr, int rows, int cols, int start)
{
	int endX = cols - 1 - start;
	int endY = rows - 1 - start;
	//打印一行 
	for (int i = start; i <= endX; i++)
		cout << arr[start][i] << " ";
	//打印一列 
	for (int i = start + 1; i <= endY; i++)
		cout << arr[i][endX] << " ";
	//打印一行
	for (int i = endX - 1; i >= start; i--)
		cout << arr[endY][i] << " ";
	//打印一列
	for (int i = endY - 1; i>start; i--)
		cout << arr[i][start] << " ";
	cout << endl;										//打印也容易错，要非常注意行和列，我弄错了行列两次了 
}
void printRect(int **arr, int rows, int cols)
{
	if (!arr || rows < 1 || cols < 1)
		return;
	int start = 0;
	while (start * 2 < rows && start * 2 < cols)		//这个条件在面试的时候很不容易想到 （到底什么时候结束打印） 
	{
		printCircle(arr, rows, cols, start);
		start++;
	}
}
int main()
{
	//	int arr[4][4] = { { 1, 2, 3, 4 }, { 12, 13, 14, 5 }, { 11, 16, 13, 6 }, { 10, 9, 8, 7 } }; 用数组的话传进去需要指定行数如：arr[][4] 这样就没有通用性了 
	int **arr = new int*[4];
	int count = 0;
	for (int i = 0; i<4; i++)
		arr[i] = new int[4];
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			arr[i][j] = count++;

	printRect(arr, 4, 4);
}
