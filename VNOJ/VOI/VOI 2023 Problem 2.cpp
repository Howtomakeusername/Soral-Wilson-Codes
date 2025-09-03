#include <bits/stdc++.h>

#define int long long

using namespace std;

int inp[1500005];
pair<int,int> a[300005];
pair<int,int> itv[300005];
vector<pair<int,int>> adj[1500005];

int add;

void build(int v, int tl, int tr){
    if(tl == tr){
        adj[tl].push_back({v+add,0});
        return;
    }
    else{
        int tm = (tl+tr)/2;

        adj[v*2+add].push_back({v+add,0});
        adj[v*2+1+add].push_back({v+add,0});

        build(v*2,tl,tm);
        build(v*2+1,tm+1,tr);
    }
}

void update(int v, int tl, int tr, int l, int r, int id){
    if(l > tr || r < tl) return;
    if(l <= tl && tr <= r){
        adj[v+add].push_back({id,1});
        return;
    }
    int tm = (tl+tr)/2;
    update(v*2,tl,tm,l,r,id);
    update(v*2+1,tm+1,tr,l,r,id);
}

int dis[1500005];

void Dijkstra(int src){
    deque<int> pq;
    dis[src] = 0;
    pq.push_back(src);
    while(!pq.empty()){
        int u = pq.front();
        pq.pop_front();

        for(auto p : adj[u]){
            int v = p.first, w = p.second;
            if(dis[v] > dis[u]+w && inp[v] < inp[src]){
                dis[v] = dis[u]+w;
                if(w == 1) pq.push_back(v);
                else pq.push_front(v);
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
    freopen("INCOME.inp", "r", stdin);
    freopen("INCOME.out", "w", stdout);
    int n;
    cin >> n;
    add = n;

    build(1,1,n);
    for(int i = 1; i <= 5*n; i++) dis[i] = 1e9;

    for(int i = 1; i <= n; i++){
        cin >> a[i].first;
        a[i].second = i;
        inp[i] = a[i].first;
    }

    for(int i = 1; i <= n; i++){
        int l,r;
        cin >> l >> r;
        itv[i] = {l,r};
        update(1,1,n,l,r,i);
    }

    sort(a+1,a+1+n, greater<pair<int,int>>());
    for(int i = 1; i <= n; i++) if(dis[a[i].second] == 1e9){
        dis[a[i].second] = 0;
        Dijkstra(a[i].second);
        //timer++;
        //for(int i = 1; i <= n; i++) cout << dis[i] << ' ' << i << endl;
        //cout << endl;
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        //cout << dis[i] << ' ' << i << endl;
        ans = max(ans, dis[i]);
    }
    if(ans) cout << ans+1;
    else cout << 0;
    return 0;
}
