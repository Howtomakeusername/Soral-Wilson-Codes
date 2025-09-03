#include<bits/stdc++.h>

using namespace std;

#define int long long

int a[100005];
int req[100005];
int dp[100005][100];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("WHOME.inp", "r", stdin);
    freopen("WHOME.out", "w", stdout);
    int n,m,p,c;
    cin >> n >> m >> p >> c;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a+1,a+1+n);
    for(int i = 1; i <= m; i++) cin >> req[i];

    for(int i = 0; i <= n+1; i++) for(int mask = 0; mask < (1<<m); mask++) dp[i][mask] = -1e18;
    dp[1][0] = 0;

    for(int i = 1; i <= n; i++) for(int mask = 0; mask < (1<<m); mask++){
        dp[i+1][mask] = max(dp[i+1][mask], dp[i][mask]);
        for(int j = 0; j < m; j++){
            if(i + req[j+1] <= n+1){
                int d = a[i+req[j+1]-1] - a[i];
                dp[i+req[j+1]][mask | (1<<j)] = max(dp[i+req[j+1]][mask | (1<<j)], dp[i][mask] + p-(d*d)*c);
            }
        }
    }

    cout << dp[n+1][(1<<m)-1];
    return 0;
}
