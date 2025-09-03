#include <bits/stdc++.h>

using namespace std;

int a[2005];
int p[2005];
int t[2005];

int n,d;

void update(int pos, int val){
    for(; pos <= n; pos += (pos & -pos)) t[pos] = max(t[pos], val);
}

int query(int pos){
    int res = 0;
    for(; pos; pos -= (pos & -pos)){
        res = max(res, t[pos]);
    }
    return res;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> d;
    n = 2*n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        p[a[i]] = i;
    }

    int ans = 0;
    for(int x = 1; x < n; x++){
        memset(t,0,sizeof(t));
        for(int i = x; i >= 1; i--){
            vector<pair<int,int>> v;
            for(int j = max(a[i]-d,1); j <= min(a[i]+d,2*n); j++) if(p[j] > x){
                int res = query(n-p[j]-1+1);
                ans = max(ans, res+1);
                v.push_back({n-p[j]+1, res+1});
            }

            for(auto pp : v) update(pp.first,pp.second);
        }
    }
    cout << ans;
    return 0;
}
