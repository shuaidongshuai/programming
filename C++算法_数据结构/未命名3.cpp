#include <iostream>
#include <string>
using namespace std;

int* get(int *p, int n){
	int sum = 0;
	for (int i = 0; i < n; ++i){
		sum += p[i];
	}
	int *res = new int[2]{-1};
	int temp;
	int k = 0;
	while(k <= 1){
		temp = rand() % sum + 1;
		int i = 0;
		for (; i < n; ++i){
			temp -= p[i];
			if (temp < 0)
				break;
		}
		if (res[0] == i)
			continue;
		res[k++] = i;
	}
	return res;
}

int main(){
	int n;
	int *p = new int[1024];
	cin >> n;
	for (int i = 0; i < n; ++i){
		cin >> p[i];
	}
	int **arr = new int*[4];
	for (int i = 0; i < 4; ++i){
		arr[i] = new int[1];
		arr[i][0] = 0;
	}
	for (int i = 0; i < 10000; ++i){
		int *res = get(p, n);
		arr[res[0]][0]++;
		arr[res[1]][0]++;
		delete res;
	}
	for (int i = 0; i < 4; ++i){
		cout << i << "´ÎÊý" << arr[i][0] << endl;
	}

}
/*
4 1 2 3 4
*/
