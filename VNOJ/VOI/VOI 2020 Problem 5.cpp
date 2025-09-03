#include <bits/stdc++.h>

using namespace std;

pair<pair<int,int>,pair<int,int>> p[400005];
vector<pair<pair<int,int>,int>> px[400005];
vector<pair<pair<int,int>,int>> py[400005];

vector<int> adj[400005];
int in[400005], low[400005];
int sz[400005];

int ans = 1e9;
vector<pair<int,int>> bridge;
int timer = 0;
int n;

void dfs(int v, int p){
    in[v] = low[v] = ++timer;
    sz[v] = 1;
    for(auto u : adj[v]) if(u != p){
        if(in[u]) low[v] = min(low[v], in[u]);
        else{
            dfs(u,v);
            sz[v] += sz[u];
            if(low[u] > in[v]) bridge.push_back({u,v});
            low[v] = min(low[v], low[u]);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("seqdiv.inp", "r", stdin);
//    freopen("seqdiv.out", "w", stdout);
    cin >> n;
    vector<int> vx, vy;

    for(int i = 1; i <= n; i++){
        cin >> p[i].first.first >> p[i].first.second >> p[i].second.first >> p[i].second.second;
        vx.push_back(p[i].first.first); vx.push_back(p[i].second.first);
        vy.push_back(p[i].first.second); vy.push_back(p[i].second.second);
    }

    sort(vx.begin(), vx.end()); sort(vy.begin(), vy.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    vy.erase(unique(vy.begin(), vy.end()), vy.end());

    for(int i = 1; i <= n; i++){
        p[i].first.first = lower_bound(vx.begin(), vx.end(), p[i].first.first) - vx.begin() + 1;
        p[i].first.second = lower_bound(vy.begin(), vy.end(), p[i].first.second) - vy.begin() + 1;
        p[i].second.first = lower_bound(vx.begin(), vx.end(), p[i].second.first) - vx.begin() + 1;
        p[i].second.second = lower_bound(vy.begin(), vy.end(), p[i].second.second) - vy.begin() + 1;

        int x = p[i].first.first, y = p[i].first.second, z = p[i].second.first, t = p[i].second.second;

        px[x].push_back({{t,1},i});
        px[x].push_back({{y+1,-1},i});
        px[z].push_back({{t,1},i});
        px[z].push_back({{y+1,-1},i});

        py[y].push_back({{x,1},i});
        py[y].push_back({{z+1,-1},i});
        py[t].push_back({{x,1},i});
        py[t].push_back({{z+1,-1},i});
    }

    for(int i = 1; i <= vx.size(); i++){
        sort(px[i].begin(), px[i].end());

        set<int> s;
        for(auto pp : px[i]){
            if(pp.first.second == 1) s.insert(pp.second);
            else{
                for(auto id : s){
                    adj[pp.second].push_back(id);
                    adj[id].push_back(pp.second);
                }
                s.erase(pp.second);
            }
        }
    }

    for(int i = 1; i <= vy.size(); i++){
        sort(py[i].begin(), py[i].end());

        set<int> s;
        for(auto pp : py[i]){
            if(pp.first.second == 1) s.insert(pp.second);
            else{
                for(auto id : s){
                    adj[pp.second].push_back(id);
                    adj[id].push_back(pp.second);
                }
                s.erase(pp.second);
            }
        }
    }

    for(int i = 1; i <= n; i++) if(!in[i]){
        bridge.clear();
        dfs(i,i);
        for(auto pp : bridge){
            ans = min(ans, abs(sz[pp.first] - (sz[i] - sz[pp.first])));
        }
    }
    if(ans != 1e9) cout << ans;
    else cout << -1;
    return 0;
}
