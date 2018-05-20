/*
给定一个字符串s，你可以从中删除一些字符，使得剩下的串是一个回文串。如何删除才能使得回文串最长呢？
输出需要删除的字符个数。
输入例子1:
abcda
google
输出例子1:
2
2
*/
#include <iostream>
#include <string>
using namespace std;
int max(int a, int b){
	return a > b ? a : b;
}
int Construct(string str){
	int size = str.size();
	int *arr[size + 1];
	for(int i = 0; i < size + 1; ++i)
		arr[i] = new int[size + 1]();
	int m = 0;
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			if(str[i] == str[size - 1 - j])
				arr[i + 1][j + 1] = arr[i][j] + 1;
			else
				arr[i + 1][j + 1] = max(arr[i][j + 1], arr[i + 1][j]);
		}
	}
	return size - arr[size][size];	
}

int main(){
	string str;
	while(cin >> str){
		cout << Construct(str) << endl;
	}
}
