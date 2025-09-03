#include<bits/stdc++.h>

using namespace std;

pair<int,int> a[400005];
int dp[400005];
int trace[400005];

pair<int,int> ans[400005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    int n;
    while(cin >> n){
        if(n == 0) break;
        n *= 2;

        for(int i = 1; i <= n; i++){
            cin >> a[i].first;
            a[i].second = i;
        }

        sort(a+1,a+1+n);
        for(int i = 1; i <= n; i++) dp[i] = 1e9;

        for(int i = 4; i <= n; i += 2){
            if(i >= 4){
                int val = max({a[i].first - a[i-1].first , a[i-2].first - a[i-3].first ,
                               a[i].first - a[i-2].first , a[i-1].first - a[i-3].first });
                if(dp[i] > max(dp[i-4],val)){
                    dp[i] = max(dp[i-4],val);
                    trace[i] = i-4;
                }
            }if(i >= 6){
                int val = max({a[i].first - a[i-1].first , a[i-2].first - a[i-4].first, a[i-3].first - a[i-5].first,
                               a[i].first - a[i-2].first , a[i-1].first - a[i-3].first, a[i-4].first - a[i-5].first});
                if(dp[i] > max(dp[i-6],val)){
                    dp[i] = max(dp[i-6],val);
                    trace[i] = i-6;
                }
            }
        }

        int cur = n;
        while(cur){
            if(trace[cur] == cur-4){
                int i = cur;
                ans[a[i].second] = {a[i-1].second, a[i-2].second};
                ans[a[i-1].second] = {a[i].second, a[i-3].second};
                ans[a[i-2].second] = {a[i-3].second, a[i].second};
                ans[a[i-3].second] = {a[i-2].second, a[i-1].second};
            }else{
                int i = cur;
                ans[a[i].second] = {a[i-1].second, a[i-2].second};
                ans[a[i-1].second] = {a[i].second, a[i-3].second};
                ans[a[i-2].second] = {a[i-4].second, a[i].second};
                ans[a[i-3].second] = {a[i-5].second, a[i-1].second};
                ans[a[i-4].second] = {a[i-2].second, a[i-5].second};
                ans[a[i-5].second] = {a[i-3].second, a[i-4].second};
            }
            cur = trace[cur];
        }

        for(int i = 1; i <= n; i++) cout << ans[i].first << ' ';
        cout << '\n';
        for(int i = 1; i <= n; i++) cout << ans[i].second << ' ';
        cout << '\n';
    }
    return 0;
}
