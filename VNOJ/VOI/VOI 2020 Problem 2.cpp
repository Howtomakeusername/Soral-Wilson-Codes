#include <bits/stdc++.h>

using namespace std;

struct Edge{
    int u,v,w;
    bool operator<(const Edge& other) const{
        return w < other.w;
    }
};

Edge a[50005],b[50005];
int n,m,s,t;
int par[50005],sz[50005];
int cnta = 1, cntb = 1, cur = 0, f[50005];
pair<int, int> rollback[50005];

int find_set(int u){
    if(par[u]==u)return u;
    return find_set(par[u]);
}

void union_sets(int u,int v){
    u = find_set(u); v = find_set(v);
    if(u != v){
        if(sz[u]>sz[v]) swap(u,v);
        cur++;
        rollback[cur]={u,sz[u]};
        sz[v]+=sz[u];
        par[u]=v;
    }
}

void rb(int ti){
     while(cur > ti){
        pair<int,int> x = rollback[cur];
        int v = par[x.first];
        par[x.first] = x.first;
        sz[v] -= sz[x.first];
        sz[x.first] = x.second;
        cur--;
    }
}

void dp(int l,int r,int from,int to){
    if(l > r) return;
    int mid = (l+r)/2;
    int base = cur;
    for(int i = l; i <= mid; i++) union_sets(b[i].u,b[i].v);

    for(int i = from; i <= to; i++){
        union_sets(a[i].u,a[i].v);
        if(find_set(s) == find_set(t)){
            f[mid]=i;
            break;
        }
    }

    rb(base);
    if(f[mid]){
        for(int i = from; i <= f[mid]; i++) union_sets(a[i].u,a[i].v);
        dp(l,mid-1,f[mid],to);
        rb(base);
    }

    for(int i = l; i <= mid; i++) union_sets(b[i].u,b[i].v);

    if(f[mid]) dp(mid+1,r,from,f[mid]);
    else dp(mid+1,r,from,to);
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    cin >> n >> m >> s >> t;
    for(int i = 1; i <= m; i++){
        int c,u,v,w;
        cin >> c >> u >> v >> w;
        if(c == 1){
            a[cnta] = {u,v,w};
            cnta++;
        }else{
            b[cntb] = {u,v,w};
            cntb++;
        }
    }

    for(int i = 1; i <= n; i++){
        par[i] = i;
        sz[i] = 1;
    }

    sort(a+1,a+cnta+1) ;
    sort(b+1,b+cntb+1);
    dp(1,cntb,1,cnta);
    int ans = 2e9;
    for(int i = 1; i <= cntb; i++) if(f[i]) ans = min(ans,a[f[i]].w+b[i].w);
    cout << ans;
}
