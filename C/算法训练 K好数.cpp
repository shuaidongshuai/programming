/*
如果一个自然数N的K进制表示中任意的相邻的两位都不是相邻的数字，那么我们就说这个数是K好数。
求L位K进制数中K好数的数目。
例如K = 4，L = 2的时候，
所有K好数为11、13、20、22、30、31、33 共7个。由于这个数目很大，请你输出它对1000000007取模后的值。

输入格式
输入包含两个正整数，K和L。

输出格式
输出一个整数，表示答案对1000000007取模后的值。 
样例输入
4 2 
样例输出
7 
简单DP，dp[i][j],其中i代表的是数字有几位，j代表首位放j的情况有几种
用F[i][j]表示长为i，最后一位数字是j的K好数的个数，则 F[i][j]=\sum F[i-1][k]，其中|j-k|!=1。
*/
#include <stdio.h>
#include <string.h>
using namespace std;
#define mod 1000000007
__int64 dp[105][105];

int main()
{
    int k,l,i,j,x;
    scanf("%d%d",&k,&l);
    for(i = 0; i<k; i++)
        dp[1][i] = 1;
        
    for(i = 2; i<=l; i++)//L位K进制
        for(j = 0; j<k; j++)
            for(x = 0; x<k; x++)
                if(x!=j-1&&x!=j+1)//本位的数字与前面的数字是不能相邻的
                {
                    dp[i][j]+=dp[i-1][x];
                    dp[i][j]%=mod;
                }
    __int64 sum = 0;
    for(i = 1; i<k; i++)
    {
        sum+=dp[l][i];
        sum%=mod;
    }
    printf("%I64d\n",sum%mod);

    return 0;
} 

