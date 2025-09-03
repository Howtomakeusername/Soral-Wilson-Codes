#include <bits/stdc++.h>

using namespace std;

#define int long long

const int lg = 20;
const int mod = 1e9+7;

int cnt[2000005];
int dp[2000005];
int fact[2000005];
int invmod[2000005];
int invfact[2000005];

int nCr(int n, int r){
    if(n < r) return 0;
    return ((fact[n] * invfact[r])%mod * invfact[n-r])%mod;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("connect.inp","r",stdin);
//    freopen("connect.out","w",stdout);
    int n,k,l,r;
    cin >> n >> k >> l >> r;

    fact[0] = 1;
    for(int i = 1; i <= n; i++) fact[i] = (fact[i-1]*i)%mod;
    invmod[1] = 1;
    for(int i = 2; i <= n; i++) invmod[i] = mod - (mod/i * invmod[mod%i])%mod;
    invfact[0] = 1;
    for(int i = 1; i <= n; i++) invfact[i] = (invfact[i-1] * invmod[i])%mod;


    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        cnt[x]++;
    }

    for(int i = 0; i < lg; i++) for(int mask = 0; mask < (1LL<<lg); mask++){
        if(mask & (1LL<<i)) cnt[mask] += cnt[mask ^ (1LL<<i)];
    }


    for(int mask = 0; mask < (1LL<<lg); mask++){
        int s = -1;
        if(__builtin_popcountll(mask)%2) s = 1;
        dp[mask] = s*nCr(cnt[mask],k);
        //cout << dp[mask] << ' ' << mask << endl;
    }

    for(int i = 0; i < lg; i++) for(int mask = 0; mask < (1LL<<lg); mask++){
        if(mask & (1LL<<i)){
            dp[mask] += dp[mask ^ (1LL<<i)];
            dp[mask] %= mod;
        }
    }

    int ans = 0;
    for(int mask = l; mask <= r; mask++) if(mask%3 == 0){
        if(__builtin_popcountll(mask)%2) ans += dp[mask];
        else ans -= dp[mask];
        ans %= mod; ans += mod; ans %= mod;
    }

    cout << ans;
    return 0;
}
