#include<bits/stdc++.h>

using namespace std;

#define int long long

const int mod = 1e9+7;

int a[2005];
int dp[2005][2005];
int n,b;

namespace Sub1{
    int ans = 0;

    void Check(){
        int cur = 0;
        int flag = 1;
        for(int i = n; i >= 1; i--){
            if(a[i] + cur > b){
                flag = 0;
                break;
            }

            if(a[i] > 0) cur++;
        }

        if(flag) ans++;
    }

    void Recur(int id){
        if(id == n+1){
            Check();
            return;
        }

        if(a[id] == -1){
            for(int i = 0; i <= id-1; i++){
                a[id] = i;
                Recur(id+1);
                a[id] = -1;
            }
        }else Recur(id+1);
    }

    void solve(){
        Recur(1);
        cout << ans;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("GRAPH.inp", "r", stdin);
    freopen("GRAPH.out", "w", stdout);
    cin >> n >> b;
    for(int i = 1; i <= n; i++) cin >> a[i];

    if(n <= 6){
        Sub1::solve();
        return 0;
    }

    dp[n+1][0] = 1;

    for(int i = n; i >= 1; i--){
        for(int j = 0; j <= min(b,n-i); j++){
            if(a[i] == -1){
                //a[i] = 0
                dp[i][j] += dp[i+1][j];
                dp[i][j] %= mod;
                //a[i] = 1...b-j
                if(min(i-1,b-j) > 0 && j < b){
                    dp[i][j+1] += dp[i+1][j] * min(i-1,b-j);
                    dp[i][j+1] %= mod;
                }
            }else{
                if(a[i] == 0) dp[i][j] = dp[i+1][j];
                else if(a[i] + j <= b && j < b){
                    dp[i][j+1] = dp[i+1][j];
                }
            }
        }
    }

    int ans = 0;
    for(int j = 0; j <= min(b,n); j++){
        ans += dp[1][j];
        ans %= mod;
    }
    cout << ans;

    return 0;
}
