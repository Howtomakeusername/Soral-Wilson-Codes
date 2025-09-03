#include <bits/stdc++.h>

using namespace std;

#define int long long

int a[505][505];
int pf[505][505];

signed main(){
    ios_base::sync_with_stdio (0);
	cin.tie (0);
//    freopen("test.inp", "r", stdin);
//    freopen("test.out", "w", stdout)
    int n,k,r,p;
    cin >> n >> k >> r >> p;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> a[i][j];
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++){
        pf[i][j] = pf[i-1][j] + pf[i][j-1] - pf[i-1][j-1] + a[i][j];
    }

    int ans = 0;
    while(k--){
        vector<pair<int,int>> vec;
        for(int i = 1; i <= p; i++){
            int x,y;
            cin >> x >> y;
            vec.push_back({x,y});
        }

        int res = 0;
        for(int mask = 1; mask < (1<<p); mask++){
            int x = 0, y = 0, u = n, v = n;
            for(int i = 0; i < p; i++) if (mask & (1<<i)){
                x = max(x, vec[i].first);
                y = max(y, vec[i].second);
                u = min(u, vec[i].first + r - 1);
                v = min(v, vec[i].second + r - 1);
            }
            if(x > u || y > v) continue;

            if(__builtin_popcount(mask)%2) res += pf[u][v] - pf[x-1][v] - pf[u][y-1] + pf[x-1][y-1];
            else res -= pf[u][v] - pf[x-1][v] - pf[u][y-1] + pf[x-1][y-1];
        }
        ans = max(ans, res);
    }
    cout << ans;

    return 0;
}
