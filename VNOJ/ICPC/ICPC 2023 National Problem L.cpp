#include<bits/stdc++.h>

using namespace std;

int a[10005];
int ans[10005];

int cnt[10005];
int mp[10005];

void add(int i){
    ans[i] = max(ans[i], mp[cnt[i]+1]+1);
    cnt[i]++;
    mp[cnt[i]]++;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,k;
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++) cin >> a[i];
    for(int l = 1; l <= m; l++){
        mp[0] = n;
        for(int r = l; r <= min(m,l+k-1); r++) add(a[r]);
        for(int i = 1; i <= n; i++){
            ans[i] = max(ans[i], mp[cnt[i]+1]+1);
            cnt[i] = 0;
        }
        for(int i = 0; i <= k; i++) mp[i] = 0;
    }

    for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}
