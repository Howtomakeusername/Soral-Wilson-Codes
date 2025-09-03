#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<pair<int,int>> adj[100005];
pair<int,int> path[100005];
vector<int> node;

bool check[15];
int d1[15][100005];
int d2[15][100005];

int deg[100005];

int n,m,k;

void Dijkstra1(int id, int src){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    for(int i = 1; i <= n; i++) d1[id][i] = 1e18;
    d1[id][src] = 0;
    pq.push({0,src});

    while(!pq.empty()){
        int c = pq.top().first, u = pq.top().second;
        pq.pop();
        if(c > d1[id][u]) continue;
        for(auto p : adj[u]){
            int v = p.first, w = p.second;
            if(d1[id][v] > c+w){
                d1[id][v] = c+w;
                pq.push({d1[id][v],v});
            }
        }
    }
}

void Dijkstra2(int id, int src){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    for(int i = 1; i <= n; i++) d2[id][i] = 1e18;
    d2[id][src] = 0;
    pq.push({0,src});

    while(!pq.empty()){
        int c = pq.top().first, u = pq.top().second;
        pq.pop();
        if(c > d2[id][u]) continue;
        for(auto p : adj[u]){
            int v = p.first, w = p.second;
            if(d2[id][v] > c+w){
                d2[id][v] = c+w;
                pq.push({d2[id][v],v});
            }
        }
    }
}

int d[100005];
vector<pair<int,int>> trace[100005];

void BuilDAG(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(int i = 1; i <= n; i++) d[i] = 1e18;
    d[path[1].first] = 0;
    pq.push({0,path[1].first});
    while(!pq.empty()){
        int c = pq.top().first, u = pq.top().second;
        pq.pop();
        if(c > d[u]) continue;
        for(auto p : adj[u]){
            int v = p.first, w = p.second;
            if(d[v] > c+w){
                d[v] = c+w;
                trace[v].clear();
                trace[v].push_back({u,w});
                pq.push({d[v],v});
            }else if(d[v] == c+w){
                trace[v].push_back({u,w});
            }
        }
    }
}

vector<pair<int,int>> dag[100005];
map<pair<int,int>, bool> mp;

int dp[100005][35][7];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("LIGHT.inp","r",stdin);
//    freopen("LIGHT.out","w",stdout);
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    cin >> path[1].first >> path[1].second;

    for(int i = 2; i <= k; i++){
        int p;
        cin >> p;
        if(p){
            node.push_back(i);
            check[i] = true;
        }
        cin >> path[i].first >> path[i].second;
    }

    for(int i = 2; i <= k; i++){
        Dijkstra1(i,path[i].first);
        Dijkstra2(i,path[i].second);
    }
    BuilDAG();
    queue<int> q;
    for(int i = 1; i <= n; i++){
        for(auto p : trace[i]){
            //cout << p.first << ' ' << i << ' ' << p.second << endl;
            dag[p.first].push_back({i,p.second});
            deg[i]++;
        }
        if(deg[i] == 0) q.push(i);
    }

    for(int u = 1; u <= n; u++){
        for(auto p : dag[u]){
            int v = p.first, w = p.second;
            for(int c = 2; c <= k; c++) if(!check[c]){
                if((d1[c][u] + w + d2[c][v]) == d1[c][path[c].second]) mp[{u,v}] = true;
            }
        }
    }

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for(auto v : dag[u]){
            deg[v.first]--;
            if (deg[v.first] == 0) q.push(v.first);
        }
    }

    int sz = node.size();
    for(int i = 1; i <= n; i++){
        int u = topo[i-1];
        //cout << "CUR : " << u << endl;
        for(auto p : dag[u]){
            int v = p.first, w = p.second;
            //cout << "TO : " << v << endl;
            int res = (mp.find({u,v}) != mp.end());

            for(int mask = 0; mask < (1LL<<sz); mask++){
                int maxx = 0;
                if(mask){
                    for(int cur = 1; cur <= sz; cur++) if( mask & (1LL<<(cur-1LL)) ){
                        int c = node[cur-1];
                        maxx = max(maxx, dp[u][mask][cur]);
                        if((d1[c][u] + w + d2[c][v]) == d1[c][path[c].second]) dp[v][mask][cur] = max(dp[v][mask][cur], dp[u][mask][cur] + w);
                        else dp[v][mask][0] = max(dp[v][mask][0], dp[u][mask][cur] + res*w);
                    }
                }

                dp[v][mask][0] = max(dp[v][mask][0], max(dp[u][mask][0],maxx) + res*w);
                for(int cur = 1; cur <= sz; cur++) if( (mask & (1LL<<(cur-1LL))) == 0 ){
                    int c = node[cur-1];
                    if((d1[c][u] + w + d2[c][v]) == d1[c][path[c].second]) dp[v][mask|(1LL<<(cur-1LL))][cur] = max(dp[v][mask|(1LL<<(cur-1LL))][cur], max(dp[u][mask][0],maxx) + w);
                }
            }
        }
    }

    int ans = 0;
    for(int mask = 0; mask < (1<<sz); mask++) for(int cur = 0; cur <= sz; cur++){
        ans = max(ans, dp[path[1].second][mask][cur]);
    }

    cout << ans;
    return 0;
}
