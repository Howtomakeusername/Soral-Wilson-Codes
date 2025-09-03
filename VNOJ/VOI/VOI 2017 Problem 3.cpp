#include <bits/stdc++.h>

using namespace std;

#define int long long

pair<int,pair<int,int>> e[100005];
int par[100005], sz[100005];
vector<pair<int,int>> adj[100005];

int find_set(int v){
    if(par[v] == v) return v;
    return par[v] = find_set(par[v]);
}

void union_set(int u, int v){
    u = find_set(u);
    v = find_set(v);
    if(u != v){
        if(sz[u] < sz[v]) swap(u,v);
        par[v] = u;
        sz[u] += sz[v];
    }
}

const int l = 18;

int in[100005], out[100005];
int up[100005][20], maxx[100005][20], minn[100005][20];
int dep[100005];

int timer = 0;
int root = 0;

void dfs(int v, int p, int w){
    in[v] = ++timer;
    up[v][0] = p;
    maxx[v][0] = w;
    minn[v][0] = w;

    for(int i = 1; i <= l; i++){
        up[v][i] = up[up[v][i-1]][i-1];
        maxx[v][i] = max(maxx[v][i-1], maxx[up[v][i-1]][i-1]);
        minn[v][i] = min(minn[v][i-1], minn[up[v][i-1]][i-1]);
    }

    if(v == root) for(int i = 0; i <= l; i++) minn[v][i] = 1e9;

    for(auto u : adj[v]) if(u.first != p){
        dep[u.first] = dep[v]+1;
        dfs(u.first,v,u.second);
    }
    out[v] = ++timer;
}

bool is_anc(int u, int v){
    return in[u] <= in[v] && out[v] <= out[u];
}

int cal(int u, int v, int w){
    if(dep[u] < dep[v]) swap(u,v);

    int m1 = w, m2 = w;

    for(int i = l; i >= 0; i--){
        if(!is_anc(up[u][i],v)){
            m1 = max(m1, maxx[u][i]);
            m2 = min(m2, minn[u][i]);
            u = up[u][i];
        }
    }
    m1 = max(m1,maxx[u][0]);
    m2 = min(m2,minn[u][0]);
    u = up[u][0];
    if(u == v) return m1+m2;

    for(int i = l; i >= 0; i--){
        if(!is_anc(up[v][i],u)){
            m1 = max(m1, maxx[v][i]);
            m2 = min(m2, minn[v][i]);
            v = up[v][i];
        }
    }
    m1 = max(m1,maxx[v][0]);
    m2 = min(m2,minn[v][0]);
    v = up[v][0];
    return m1+m2;
}

int n,m;
int check[100005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("test.inp","r",stdin);
//    freopen("test.out","w",stdout);

    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        par[i] = i;
        sz[i] = 1;
    }

    for(int i = 1; i <= m; i++) cin >> e[i].second.first >> e[i].second.second >> e[i].first;
    sort(e+1,e+1+m, greater<pair<int,pair<int,int>>>());
    for (int i = 1; i <= m; i++){
        int u = e[i].second.first, v = e[i].second.second;
		if(find_set(u) != find_set(v)){
			union_set(u,v);
			adj[u].push_back({v,e[i].first});
            adj[v].push_back({u,e[i].first});
		}else check[i] = 1;
	}

	for (int i = 1; i <= n; i++) if(!in[i]){
	   root = i;
	   dfs(i,i,0);
	}
	int ans = 0;
    for (int i = 1; i <= m; i++) if(check[i]) ans = max(ans, cal(e[i].second.first, e[i].second.second, e[i].first));
    cout << ans;
    return 0;
}
