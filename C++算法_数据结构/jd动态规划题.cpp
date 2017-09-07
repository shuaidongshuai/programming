#include <iostream>
using namespace std;

void initarr(double **&arr,int n)
{
	arr = new double*[n];
	for(int i = 0;i<n;i++)
		arr[i] = new double[n];
}

int main()
{
	int n;
	cin>>n;
	int *p = new int[n]; 
	for(int i = 0; i<n; i++)
		cin>>p[i];
	int low = (3 * n + 4) / 5;//至少要做对的题目
	//前i题对j个的概率    ★有这句话就能写出动态规划
	double **res;
	initarr(res,n+1);
	res[0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		res[i][0] = res[i - 1][0] * (100 - p[i - 1]) / 100;
		for(int j = 1; j <= i; j++)
			res[i][j] = res[i - 1][j - 1] * p[i] / 100 + res[i - 1][j] * (100 - p[i]) / 100;
	}
	double sum = 0;
	for(int i = low; i<=n; i++)
		sum += res[n][i];
	printf("%.5f",sum);
	
	return 0;
} 
