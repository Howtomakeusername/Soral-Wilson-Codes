#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> adj[1005];
vector<pair<int,int>> rev[1005];
int e[1005][1005];

int d[1005];
vector<int> trace[1005];
int n,m,t,k;

void Dijkstra(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    d[t] = 0;
    pq.push({0,t});
    while(!pq.empty()){
        int c = pq.top().first, u = pq.top().second;
        pq.pop();
        if(c > d[u]) continue;
        for(auto p : rev[u]){
            int v = p.first, w = p.second;
            if(d[v] > c+w){
                d[v] = c+w;
                pq.push({d[v],v});
                trace[v].clear();
                trace[v].push_back(u);
            }else if(d[v] == c+w) trace[v].push_back(u);
        }
    }
}

vector<int> dag[1005];
int deg[1005];
int vis[1005][105];

int minn = 1e9;
int dp[1005][105];

int ok = 0;
vector<int> path;

void dfs(int u, int c){
    path.push_back(u);
    vis[u][c] = 1;
    //cout << u << ' ' << k << ' ' << c << endl;
    if (u == t){
        if(k == 1) ok = 1;
        else{
            for(auto p : adj[u]){
                int v = p.first;
                if(v == u) if(k > dp[v][0]) k -= dp[v][0];
            }
            if(k == 1) ok = 1;
            path.push_back(u);
        }
        return;
    }

    sort(adj[u].begin(), adj[u].end());
    for(auto p : adj[u]){
        int v = p.first, w = p.second;
        if(v == u){
            if(!vis[v][0]){
                if(k > dp[v][0]) k -= dp[v][0];
                else{
                    dfs(v, 0);
                    return;
                }
            }
        }
        else{
            int val = c - (d[v] + w - d[u]);
            if (val < 0) continue;
            if (k > dp[v][val]) k -= dp[v][val];
            else{
                if(!vis[v][val])dfs(v, val);
                return;
            }
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("test.inp","r",stdin);
//    freopen("test.out","w",stdout);
    cin >> n >> m >> t >> k;

    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = 1e9;

    for(int i = 1; i <= m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        e[u][v] = min(e[u][v],w);
        rev[v].push_back({u,w});
        minn = min(minn,w);
    }

    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++){
        if(e[i][j] != 1e9){
            adj[i].push_back({j,e[i][j]});
        }
    }

    for(int i = 1; i <= n; i++) d[i] = 1e9;
    Dijkstra();
    //for(int i = 1; i <= n; i++) cout << d[i] << ' ' << i << endl;
    if(d[1] == 1e9){
        cout << -1;
        return 0;
    }

    queue<int> q;
    vector<int> topo;
    for(int i = 1; i <= n; i++) if(d[i] != 1e9){
        for(auto p : trace[i]){
            deg[i]++;
            dag[p].push_back(i);
        }
        if(deg[i] == 0) q.push(i);
    }

    while(!q.empty()){
        int u = q.front();
        topo.push_back(u);
        q.pop();
        for(auto v : dag[u]){
            deg[v]--;
            if(deg[v] == 0) q.push(v);
        }
    }

    dp[t][0] = 1;
    for(auto u : topo){
        int flag = 0;
        for(auto p : rev[u]){
            int v = p.first, w = p.second;
            if(v == u){
                if(w == minn) flag = 1;
                break;
            }
        }

        if(flag){
            dp[u][minn] += dp[u][0];
            //cout << u << endl;
        }

        for(int c = 0; c <= minn; c++) if(dp[u][c]){
            for(auto p : rev[u]){
                int v = p.first, w = p.second;
                if(v == u){
                    flag = 1;
                    continue;
                }
                int newc = c+d[u]+w-d[v];
                if(newc < 0) continue;
                if (newc <= minn){
                    dp[v][newc] += dp[u][c];
                    dp[v][newc] = min(dp[v][newc],(int)1e9);
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) for(int c = 1; c <= minn; c++){
        dp[i][c] += dp[i][c-1];
        dp[i][c] = min(dp[i][c],(int)1e9);
        //cout << dp[i][c] << ' ' << i << ' ' << c << ' ' << "DP" << endl;
    }

    dfs(1,minn);
    if(!ok) cout << -1;
    else{
        cout << path.size() << '\n';
        for(auto i : path) cout << i << ' ';
    }

    return 0;
}
