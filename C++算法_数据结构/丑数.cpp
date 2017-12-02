#include <iostream>
#include <vector>
using namespace std;
/*
	把只包含因子2、3和5的数称作丑数（Ugly Number）。
	例如6、8都是丑数，但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。
	求按从小到大的顺序的第N个丑数。
*/
int min(int a, int b, int c){
	int m = a < b ? a : b;
	return m < c ? m : c;
}
int GetUglyNumber_Solution(int index) {
	vector<int> v(index);
	v[0] = 1;
	int t2 = 0, t3 = 0, t5 = 0;
	for(int i = 1; i < index; ++i){
		v[i] = min(2 * v[t2], 3 * v[t3], 5 * v[t5]);
		if(v[i] == 2 * v[t2])
			++t2;
		if(v[i] == 3 * v[t3])//������else if ��Ϊ�п��� ����������� 
			++t3;
		if(v[i] == 5 * v[t5])
			++t5;
	}
	return v[index - 1];
}
int main(){
	cout << GetUglyNumber_Solution(7) << endl;
}
