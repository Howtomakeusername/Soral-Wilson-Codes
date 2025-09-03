#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<int> adj[1005];
int dp[1005][1005][10];
int sz[1005];

int n,k,a,b;

void dfs(int v, int p){
    dp[v][0][0] = 1;
    dp[v][0][1] = 1;

    for(auto u : adj[v]) if(u != p){
        dfs(u,v);
        for(int i = sz[v]; i >= 0; i--){
            for(int j = sz[u]; j >= 0; j--){
                for(int k1 = 1; k1 <= k; k1++){
                    for(int k2 = 0; k2 <= k-k1; k2++){

                        int s = i + j + (k1 < k);
                        dp[v][s][k2+k1] += dp[v][i][k2] * dp[u][j][k1];
                    }
                }
            }
        }
        sz[v] += sz[u]+1;
    }

    //cout << v << endl;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> a >> b;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,1);

    int ans = 0;
    for(int i = a; i <= b; i++) ans += dp[1][i][k];
    cout << ans;
    return 0;
}
