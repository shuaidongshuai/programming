//把自然数N分解成若干个互不相同的正整数之和，使乘积最大
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
//有一个整数n，将n分解成若干个不同自然数之和，问如何分解能使这些数的乘积最大，输出这个乘积m 
#define maxn 109
using namespace std;
long long dp[maxn][maxn];
int solve(int n){
	long long ans = 0;
	for(int i = 0; i <= n; i++)
		ans = max(ans, dp[n][i]);
	return ans;
}
int main(){
	int n;
	cin >> n;
	for(int i = 0; i <= n; i++)
		dp[0][i] = 1;					//为什么初始化的是1？ 因为要求乘积最大，如 7 拆 成了 0 + 7  那你说乘积最大是0还是7 
	for(int i = 1; i <= n; i++)			//遍历从1 - n 之间的所有整数 
		for(int j = 1; j <= i; j++)		//整数 i 这次要分解的数 
			for(int k = 0 ; k < j; k++)	//因为是不同的自然数所以k!=j 
				dp[i][j] = max(dp[i][j], dp[i - j][k] * j);//要乘积最大，需要得到拆分前乘积最大的值 
	cout << solve(n) << endl;
	
	for(int i = 0;i<=n;i++)
	{
		for(int j = 0;j<=n;j++)
			cout<<dp[i][j]<<"\t";
		cout<<endl;
	}
	return 0;
}
