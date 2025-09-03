#include <bits/stdc++.h>

using namespace std;

int a[1001][1001];
int pf[1001][1001];

int sum(int u, int v, int s, int t){
    return pf[s][t] - pf[u-1][t] - pf[s][v-1] + pf[u-1][v-1];
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("connect.inp","r",stdin);
//    freopen("connect.out","w",stdout);
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> a[i][j];
    for(int i = 1; i <= 2*n; i++) for(int j = 1; j <= 2*m; j++){
        int x = i, y = j;
        if(x > n) x -= n;
        if(y > m) y -= m;
        a[i][j] = a[x][y];
    }

    for(int i = 1; i <= 2*n; i++) for(int j = 1; j <= 2*m; j++){
        pf[i][j] = pf[i-1][j] + pf[i][j-1] - pf[i-1][j-1] + a[i][j];
    }

    int q;
    cin >> q;

    int r = 0,d = 0;
    while(q--){
        int type;
        cin >> type;
        if(type == 0){
            int x,y;
            cin >> x >> y;
            r += x; d += y;
            r %= m; d %= n;
        }else{
            int u,v,s,t;
            cin >> u >> v >> s >> t;
            u += d;
            v += r;
            s += d;
            t += r;
            cout << sum(u,v,s,t) << '\n';
        }
    }

    return 0;
}
