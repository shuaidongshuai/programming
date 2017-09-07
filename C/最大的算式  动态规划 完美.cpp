#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>

using namespace std;

#define N 105
#define ll long long

ll dp[N][N][N];
ll n,k;
ll a[N];
ll sum[N];
ll ans;

ll dfs(ll l,ll r,ll kk)
{
    if(dp[l][r][kk] != -1) return dp[l][r][kk];
    if(kk == 0){
        dp[l][r][kk] = sum[r] - sum[l - 1];
        return dp[l][r][kk];
    }
    ll i,cou;
    ll ma = 0;
    for(i = l;i <= r -1;i++){
        for(cou = 0;cou <= kk - 1;cou++){
            ma = max(ma,dfs(l,i,cou) * dfs(i + 1,r,kk - cou - 1) );
        }
    }
    if(l - r != kk){
        for(i = l;i <= r -1;i++){
            for(cou = 0;cou <= kk;cou++){
                ma = max(ma,dfs(l,i,cou) + dfs(i + 1,r,kk - cou) );
            }
        }
    }
    dp[l][r][kk] = ma;
    return dp[l][r][kk];
}

int main()
{
    //freopen("in.txt","r",stdin);
    while(scanf("%I64d%I64d",&n,&k)!=EOF){

    memset(dp,-1,sizeof(dp));
    memset(sum,0,sizeof(sum));
    ll i;
    for(i = 1;i <= n;i++){
        scanf("%I64d",&a[i]);
        sum[i] = sum[i-1] + a[i];
    }
    ans = dfs(1,n,k);
    printf("%I64d\n",ans);
    }
    return 0;
}
