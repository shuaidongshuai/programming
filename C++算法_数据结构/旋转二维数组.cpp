#include<iostream>
using namespace std;

void print(int **arr,int row,int col)
{
	for(int i = 0;i<row;i++)
	{
		for(int j = 0;j<col;j++)
			cout<<arr[i][j]<<"\t";
		cout<<endl;
	}
	cout<<"---------------------------------------"<<endl;
}

//把二维数组旋转90度
int **rotateArr(int **arr,int row,int col)
{
	if(!arr || !*arr || row < 1 || col < 1)
		return NULL;
	int **newArr = new int*[col];
	for(int i = 0;i<col;i++)
		newArr[i] = new int[row];
		
	for(int i = 0;i<row;i++)
		for(int j = 0;j<col;j++)
			newArr[j][row - 1 - i] = arr[i][j];//注意这里是row - 1 - i   不是 col - 1 - i 
	return newArr;
}

int main()
{
	int row = 3,col = 6;
	int **arr = new int*[row];
	for(int i = 0;i<row;i++)
		arr[i] = new int[col];
	int count = 0;
	for(int i = 0;i<row;i++)
		for(int j = 0;j<col;j++)
			arr[i][j] = count++;
	print(arr,row,col);
	int **newArr = rotateArr(arr,row,col);
	print(newArr,col,row);
} 
