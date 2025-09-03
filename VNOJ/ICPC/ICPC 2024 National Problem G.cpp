#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int a[666670];
int nxt[666670];
map<int,int> mp;
int dp[666670];
int cnt[666670];
int save[666670];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        int n,q;
        cin >> n >> q;
        for(int i = 1; i <= n; i++) cin >> a[i];
        nxt[n+1] = n;
        for(int i = n; i >= 1; i--){
            nxt[i] = nxt[i+1];
            if(mp.find(a[i]) != mp.end()) nxt[i] = min(nxt[i], mp[a[i]]-1);
            mp[a[i]] = i;
        }

        while(q--){
            int k;
            cin >> k;
            for(int i = n+1; i >= 0; i--) save[i] = dp[i] = cnt[i] = 0;

            int j = n;
            dp[n+1] = 0;
            cnt[n+1] = 1;
            for(int i = n; i >= 1; i--){
                if(i+k <= n+1){
                    save[dp[i+k]] += cnt[i+k];
                    if(save[dp[i+k]] >= mod) save[dp[i+k]] -= mod;
                }

                if(i+k-1 <= nxt[i]) dp[i] = dp[i+k]+1;

                while(j > nxt[i]){
                    save[dp[j+1]] -= cnt[j+1];
                    if(save[dp[j+1]] < 0) save[dp[j+1]] += mod;
                    j--;
                }

                if(dp[i]) cnt[i] = save[dp[i]-1];

                if(dp[i] < dp[i+1]){
                    dp[i] = dp[i+1];
                    cnt[i] = cnt[i+1];
                }else if(dp[i] == dp[i+1]){
                    cnt[i] += cnt[i+1];
                    if(cnt[i] >= mod) cnt[i] -= mod;
                }
            }
            cout << dp[1] << ' ' <<  cnt[1] << '\n';
        }

        for(int i = 0; i <= n+1; i++) nxt[i] = 0;
        mp.clear();
    }
    return 0;
}
