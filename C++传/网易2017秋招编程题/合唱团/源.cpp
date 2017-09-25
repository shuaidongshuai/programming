/*
题目描述
有 n 个学生站成一排，每个学生有一个能力值，牛牛想从这 n 个学生中按照顺序选取 k 名学生，
要求相邻两个学生的位置编号的差不超过 d，使得这 k 个学生的能力值的乘积最大，你能返回最大的乘积吗？

示例1
输入
3
7 4 7
2 50
输出
49
*/
#include <iostream>
#include <fstream>
using namespace std;

int max(int a, int b){
	return a > b ? a : b;
}
void swap(int &a, int &b){
	int c = a;
	a = b;
	b = c;
}

int main()
{
	int n, k, d;
	cin >> n;
	int *val = new int[n + 1];
	for (int i = 1; i <= n; ++i){
		cin >> val[i];
	}
	cin >> k >> d;

	//初始化
	long long **arr_up = new long long*[k + 1];
	long long **arr_down = new long long*[k + 1];
	for (int i = 0; i < k + 1; ++i){
		arr_up[i] = new long long[n + 1]();
		arr_down[i] = new long long[n + 1]();
	}
	for (int i = 1; i < n + 1; ++i){
		arr_up[1][i] = val[i];
		arr_down[1][i] = val[i];
	}

	for (int i = 2; i <= k; ++i){	//选i个人
		for (int j = i; j <= n; ++j){	//最大的位置编号
			int x = max(j - d, 1);
			long long sum_up = arr_up[i - 1][x] * val[j];//记录最大的数
			long long sum_down = arr_down[i - 1][x] * val[j];//记录最小的数
			if (sum_up < sum_down){
				swap(sum_up, sum_down);
			}
			for (++x; x < j; ++x){
				long long num = arr_up[i - 1][x] * val[j];
				if (num > sum_up){
					sum_up = num;
				}
				else if (num < sum_down){
					sum_down = num;
				}

				num = arr_down[i - 1][x] * val[j];
				if (num > sum_up){
					sum_up = num;
				}
				else if (num < sum_down){
					sum_down = num;
				}
			}
			arr_up[i][j] = sum_up;
			arr_down[i][j] = sum_down;
		}
	}
	//获取最大乘积
	long long max_sum = arr_up[k][k];
	for (int i = k + 1; i <= n; ++i){
		if (arr_up[k][i] > max_sum){
			max_sum = arr_up[k][i];
		}
	}
	cout << max_sum << endl;

	system("pause");
	return 0;
}
/*
测试用例:
47
-41 -5 -10 -31 -44 -16 -3 -33 -34 -35 -44 -44 -25 -48 -16 -32 -37 -8 -33 -30 -6 -18 -26 -37 -40 -30 -50 -32 -5 -41 -32 -12 -33 -22 -14 -34 -1 -41 -45 -8 -39 -27 -23 -45 -10 -50 -34
6 3
对应输出应该为:
5504557500
你的输出为:
2135936000			★★★★这个错误是因为整型没那么大  MD 

改为 long long 就全部通过了
*/
