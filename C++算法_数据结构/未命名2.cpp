#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main(){
	int k;
	int nodeVal[3];
	cin >> k >> nodeVal[0] >> nodeVal[1] >> nodeVal[2];

	int minVal = min(min(nodeVal[0], nodeVal[1]), nodeVal[2]);
	int maxVal = max(max(nodeVal[0], nodeVal[1]), nodeVal[2]);
	int left = 1;
	int right = (int)pow(2, k) - 1;
	int mid = (left + right) / 2;

	while (left < right){
		if (minVal < mid && maxVal > mid){
			break;
		}
		else if (minVal > mid){
			left = mid + 1;
			mid = (left + right) / 2;
		}
		else{
			right = mid - 1;
			mid = (left + mid) / 2;
		}
	}
	cout << mid << endl;
	return 0;
}
