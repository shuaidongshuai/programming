#include <iostream>
#include <cmath>
using namespace std;
/*
题目：n个骰子朝上的数之和为s，求s的所有可能以及概率
分析：
需要求出每个点数，然后加起来，除以6^n
点数一共就 6n-n 种可能
*/

//递归：把N个骰子分成两堆 (1,N-1) 然后点数就是左边从1 - 6 加上右边
const int oneMax = 6;//一个骰子是从1 - 6
void MakeRes(int *numRes, int n, int num, int sum){//n 一共几个骰子 num 右边堆中还有几个骰子 sum 左边骰子的点数和
	if (0 == num)
		++numRes[sum - n];
	else{
		for (int i = 1; i <= oneMax; ++i)
			MakeRes(numRes, n, num - 1, sum + i);
	}
}
void Probability(int n){
	if (n < 1) return;
	int maxNum = (oneMax - 1) * n + 1;
	int *numRes = new int[maxNum]();//里面从0开始存储最小的数5n
	MakeRes(numRes, n, n, 0);
	double total = pow(oneMax, n);
	for (int i = 0; i < maxNum; ++i){
		cout << i + n << ":" << (double)numRes[i] / total << endl;
	}
}
//非递归:骰子挨个遍历，用2个位图，轮流保存上次num出现的次数，下一个骰子点数n 加上次点数n-1,n-2,n-3,,,n-6
//想一下加一个骰子后，是不是所有点数(n)都变成了没加之前 n-1 n-2 n-3 n-4 n-5 n-6之和了===新加的骰子为上次每个数都可以从1加到6
void Probability2(int n){
	if (n < 1) return;
	int *res[2];
	int maxNum = oneMax * n;
	res[0] = new int[maxNum + 1]();
	res[1] = new int[maxNum + 1]();
	int flag = 0;
	//第一个骰子产生的数
	for (int i = 1; i <= oneMax; ++i)
		res[flag][i] = 1;
	//然后是剩下的骰子
	for (int i = 2; i <= n; ++i){
		for (int j = i; j <= maxNum; ++j){//加下一个骰子后 所有的点
			res[1 - flag][j] = 0;//清空原来的数据
			for (int k = 1; k <= oneMax; ++k){
				if (j - k > 0)
					res[1 - flag][j] += res[flag][j - k];
				else
					break;
			}
		}
		flag = 1 - flag;
	}
	double total = pow(oneMax, n);
	for (int i = n; i <= maxNum; ++i){
		cout << i << ":" << (double)res[flag][i] / total << endl;
	}
}
int main(){
	Probability(3);
	cout << "---------------------------" << endl;
	Probability2(3);
}
