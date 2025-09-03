#include <bits/stdc++.h>

using namespace std;

int q[5005];
int w[5005];
int c[5005];
long long dp[5005][5355];
int node[5005], out[5005];
vector<int> adj[5005];
int timer = 0;

void dfs(int v, int p){
    node[++timer] = v;
    for(auto u : adj[v]) if(u != p){
        dfs(u,v);
    }
    out[v] = timer;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("FOOD.inp","r",stdin);
    freopen("FOOD.out","w",stdout);
    int n,s;
    cin >> n >> s;
    for(int i = 1; i <= n; i++) cin >> q[i] >> w[i] >> c[i];
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,1);

    for(int i = 1; i <= n+1; i++) for(int j = 5350; j >= 0; j--) dp[i][j] = 1e18;

    dp[n+1][0] = 0LL;

    for(int i = n; i >= 1; i--){
        int id = node[i];
        for(int j = 5350; j >= 0; j--){
            dp[i][j] = dp[out[id]+1][j];
            for(int k = 1; k <= min(j/w[id],q[id]); k++){
                dp[i][j] = min(dp[i][j], dp[i+1][j-k*w[id]] + (long long)k*k*c[id]);
            }
            //cout << dp[i][j] << ' ' << i << ' ' << j << ' ' << id << endl;
        }
    }

    long long ans = 1e18;
    for(int i = s; i <= 5350; i++) ans = min(ans, dp[1][i]);
    if(ans != 1e18) cout << ans;
    else cout << -1;
    return 0;
}
