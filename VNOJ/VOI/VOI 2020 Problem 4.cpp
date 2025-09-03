#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> a;
vector<vector<pair<int,int>>> sw;
int n,m,k;

int Check(int c){
    vector<vector<int>> t;
    t.resize(n+2, vector<int>(m+2));
    int ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            t[i][j] += t[i-1][j] + t[i][j-1] - t[i-1][j-1];
            t[i][j] = (t[i][j]%3 + 3)%3;

            int cur = (a[i][j] + t[i][j])%3;

            if(cur != c){
                if(sw[i][j].first == 0){
                    ans = 1e8;
                    break;
                }else{
                    int res = (c-cur+3)%3;
                    ans += res;

                    int x = sw[i][j].first, y = sw[i][j].second;
                    t[i][j] += res;
                    t[x+1][j] -= res;
                    t[i][y+1] -= res;
                    t[x+1][y+1] += res;
                }
            }
        }
        if(ans == 1e8) break;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
//    freopen("test.inp", "r", stdin);
//    freopen("test.out", "w", stdout)
    cin >> n >> m >> k;
    a.resize(n+2, vector<int>(m+2));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> a[i][j];

    sw.resize(n+2, vector<pair<int,int>>(m+2));
    for(int i = 1; i <= k; i++){
        int r,c,x,y;
        cin >> r >> c >> x >> y;
        sw[r][c] = {x,y};
    }

    int ans = min(Check(1),Check(2));
    if(ans == 1e8) cout << -1;
    else cout << ans;

    return 0;
}
