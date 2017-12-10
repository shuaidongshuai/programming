#include <iostream>
#include <cstring>
using namespace std;
/* 连续子序列最大和 注意：全为负数情况*/
bool res = true;
int  MaxSumSubArr(int *arr, int len){
	if(!arr || len < 1){
		res = false;
		return 0;
	}
	int max, sum;
	max = sum = arr[0];
	for(int i = 1; i < len; ++i){
		if(sum <= 0)
			sum = arr[i];
		else
			sum += arr[i]; 
		if(max < sum)
			max = sum;
	}
	return max; 
}
void test1(){
	int arr1[]{1, 3, -5, 3, -2, 4, -5};
	int arr2[]{-1, -2, -5, -2};
	int arr3[]{};
	cout << MaxSumSubArr(arr1, sizeof(arr1) / sizeof(arr1[0])) << endl;//5
	cout << MaxSumSubArr(arr2, sizeof(arr2) / sizeof(arr2[0])) << endl;//-1
	cout << MaxSumSubArr(arr3, sizeof(arr3) / sizeof(arr3[0])) << endl;//0
}
/* 最大子矩阵的和 */
/*
思路：
正常思路： 找到起点(矩阵的左上角的点)O(n^2) 找到长、宽O(n^2) 然后遍历这个矩阵O(n^2) 时间复杂度：O(n^2) 
利用连续子序列最大和：  
必须包含第1行 - 必须包含1、2行  -  1、2、3  -  1、、、n  -  2、3  -  2、3、4 - - - 
比如必须包含 2、3行的最大子矩阵和 === 2、3行的列相加 然后求这个数据的最大连续子序列和 
*/
int MaxRectangle(int **arr, int _long, int _wide){
	if(!arr || _long < 1 || _wide < 1){
		res = false;
		return 0;
	}
	int max = 0, temp, len = _long;
	int *tempArr = new int[len];
	for(int i = 0; i < _wide; ++i){
		memset(tempArr, 0, sizeof(int) * len);
		for(int j = i; j < _wide; ++j){
			while(len--)
				tempArr[len] += arr[j][len];
			len = _long;
			temp = MaxSumSubArr(tempArr, len);
			if(max < temp)
				max = temp;
		}
	}
	delete tempArr;
	return max;
} 
void test2(){
	int n;
	while(cin >> n){
		if(n < 0)
		return; 
		int **arr = new int*[n];
		for(int i = 0 ; i < n; ++i){
			arr[i] = new int[n];
			for(int j = 0; j < n; ++j)
				cin>>arr[i][j];
		}
		
		cout << MaxRectangle(arr, n, n) << endl;
		
		while(n--)
			delete[] arr[n];
		delete[] arr;
	}
}
/* input:
4
0 -2 -7 0
9 2 -6 2
-4 1 -4 1
-1 8 0 -2
*/
int main(){
//	test1();
	test2();
    return 0;
}


