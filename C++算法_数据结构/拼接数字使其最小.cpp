#include <iostream>
#include <algorithm> 
using namespace std;
//例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。

bool cmp(int a, int b){
	string str1 = to_string(a);
	str1 += to_string(b);
	string str2 = to_string(b);
	str2 += to_string(a);
	return str1 < str2;
}

string MergerNum(int *arr, int len){
	if(!arr || len <= 0)
		return "";
	sort(arr, arr + len, cmp);
	string res;
	for(int i = 0; i < len; ++i)
		res += to_string(arr[i]);
	return res;
}

int main(){
	int arr[] = {3, 32, 321};
	cout<< MergerNum(arr,3) <<endl;
}
