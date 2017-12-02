#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main(){
	int n;
	cin>>n;
	int num = 0, count = 0, old = 0;
	int *arr = new int[n];
	for(int i = 0; i < n; ++i){
		cin>>arr[i];
		if(num == arr[i]){
			++count;
		}
		else if(!count){
			if(old > num)
				old = num;
			num = arr[i];
			++count;
		}
		else
			--count;
	}
	int c1 = 0, c2 = 0;
	for(int i = 0; i < n; ++i){
		if(arr[i] == old)
			++c1;
		else if(arr[i] == num)
			++c2;
	}
	if(c1 >= c2){
		cout<<old<<endl;
	}
	else
		cout<<num<<endl;
}
/*
6
123
466
789
456
123
890
*/

