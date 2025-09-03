#include <bits/stdc++.h>

using namespace std;

int a[1005];
int dp[1005];
int id[1005];

int timer = 0;
int n,k;

int Cal(){
    int p = 0, l = 0;
    for (p = n-1; p >= 1; p--) if (a[p] < a[p+1]) break;
    if (p <= 0) return p;

    for(l = n; l > p; l--) if (a[p] < a[l]) break;
    swap(a[p], a[l]);

    for (int i = p+1, j = n; i < j; i++, j--) swap(a[i], a[j]);
    return p;
}

bool Check(int nxt){
    for(int i = nxt; i <= n; i++){
        timer ++;
        int r = 1e9;
        for (int j = i+1; j <= n; j++){
            id[a[j]] = timer;
            r = min(r, a[j]);
        }

        int l = 0;
        for(int j = a[i]-1; j >= 1; j--){
            if (id[j] != timer){
                l = j;
                break;
            }
        }
        dp[i] = (l < r);
        if(i > 1) dp[i] &= dp[i-1];
    }
    return dp[n];
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("mbp.inp","r",stdin);
//    freopen("mbp.out","w",stdout);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];

    int cur = 0;
    int ans = 0;
    while(k--){
        if(Check(cur)) ans++;
        cur = Cal();
        if(cur <= 0) break;
    }

    cout << ans;
    return 0;
}
