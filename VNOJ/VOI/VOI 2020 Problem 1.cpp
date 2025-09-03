#include <bits/stdc++.h>

using namespace std;

#define int long long

int a[305];
int dp[305][305][305];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("seqdiv.inp", "r", stdin);
//    freopen("seqdiv.out", "w", stdout);
    int n,k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i < n; i++) dp[i][i+1][1] = abs(a[i] - a[i+1]);

    for(int len = 3; len <= n; len++){
        for(int i = 1; i <= n-len+1; i++){
            int j = i+len-1;
            for(int p = 1; p <= k; p++){
                dp[i][j][p] = max({dp[i+1][j][p], dp[i][j-1][p], dp[i+1][j-1][p-1] + abs(a[i] - a[j]), dp[i+2][j][p-1] + abs(a[i] - a[i+1]), dp[i][j-2][p-1] + abs(a[j] - a[j-1])});
            }
        }
    }

    cout << dp[1][n][k];
    return 0;
}
