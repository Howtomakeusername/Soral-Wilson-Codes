#include <bits/stdc++.h>

using namespace std;

#define int long long

int par[2000005];

int find_set(int v){
    if(par[v] == v) return v;
    return par[v] = find_set(par[v]);
}

void union_set(int u, int v){
    u = find_set(u);
    v = find_set(v);
    if(u != v){
        par[v] = u;
    }
}

vector<int> adj[2000005];
int sz[2000005];
int val[2000005];
int up[2000005];
int check[2000005];

int res = 0;
int n,m;

void get(int v, vector<int>& node){
    if(v <= n && !check[v]){
        node.push_back(v);
        check[v] = 1;
    }
    for(auto u : adj[v]) get(u,node);
}

void dfs(int v){
    int l = adj[v][0], r = adj[v][1];
    if(sz[l] < sz[r]) swap(l,r);
    if(sz[l] * 2 > n){
        //cout << val[v] << ' ' << sz[r] << ' ' << v << endl;
        res += 2 * sz[r] * val[v];
        dfs(l);
        return;
    }
    vector<int> le, ri, out;
    get(l,le);
    get(r,ri);
    //cout << res << '\n';
    get(n+m,out);
    res += val[v] * (n-1-2*out.size());
//
    vector<int> ans;

    while(out.size()){
        if(le.size() > ri.size()) ans.push_back(le.back()), le.pop_back();
        else ans.push_back(ri.back()), ri.pop_back();
        ans.push_back(out.back()); out.pop_back();
    }

    while(le.size() || ri.size()){
        if(le.size() > ri.size()) ans.push_back(le.back()), le.pop_back();
        else ans.push_back(ri.back()), ri.pop_back();
    }

    cout << res << '\n';
    for(auto i : ans) cout << i << ' ';
    cout << '\n';
    res = 0;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        cin >> n >> m;
        vector< pair<int,pair<int,int>> > e;

        for(int i = 1; i <= n; i++){
            par[i] = i;
            sz[i] = 1;
        }

        for(int i = 1; i <= m; i++){
            int u,v,w;
            cin >> u >> v >> w;
            e.push_back({w, {u,v}});
        }

        vector< pair<int,pair<int,int>> > mst;
        sort(e.begin(), e.end());
        for(auto p : e){
            int u = p.second.first, v = p.second.second;
            if(find_set(u) != find_set(v)){
                mst.push_back(p);
                union_set(u,v);
            }
        }

        m = mst.size();
        for(int i = 1; i <= n+m; i++) par[i] = i;
        for(int i = 1; i <= m; i++){
            int u = mst[i-1].second.first, v = mst[i-1].second.second;
            u = find_set(u), v = find_set(v);
            adj[i+n].push_back(u);
            adj[i+n].push_back(v);
            sz[i+n] = sz[u] + sz[v];
            union_set(i+n,u);
            union_set(i+n,v);
            up[u] = i+n;
            up[v] = i+n;

            val[i+n] = mst[i-1].first;
        }

        int root = find_set(1);
        dfs(root);

        for(int i = 1; i <= n+m; i++){
            adj[i].clear();
            sz[i] = 0;
            val[i] = 0;
            up[i] = 0;
            check[i] = 0;
        }
    }
    return 0;
}
