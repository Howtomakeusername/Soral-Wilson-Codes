#include <bits/stdc++.h>

#define int long long

using namespace std;

pair<int,int> e[100005];
vector<pair<int,int>> adj[100005];
int d1[100005], d2[100005];

void Dijkstra1(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
    pq.push({0,1});
    d1[1] = 0;
    while(!pq.empty()){
        int c = pq.top().first, u = pq.top().second;
        pq.pop();
        if(c > d1[u]) continue;
        for(auto p : adj[u]){
            int v = p.first, w = p.second;
            if(d1[v] > c+w){
                d1[v] = c+w;
                pq.push({d1[v],v});
            }
        }
    }
}

void Dijkstra2(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
    pq.push({0,2});
    d2[2] = 0;
    while(!pq.empty()){
        int c = pq.top().first, u = pq.top().second;
        pq.pop();
        if(c > d2[u]) continue;
        for(auto p : adj[u]){
            int v = p.first, w = p.second;
            if(d2[v] > c+w){
                d2[v] = c+w;
                pq.push({d2[v],v});
            }
        }
    }
}

struct Ver{
    int i, id, x, y, pos;
    bool operator<(const Ver& other) const{
        if(x == other.x) return id < other.id;
        return x < other.x;
    }
};

Ver a[300005];

int t[300005];

void update(int pos, int n){
    for(int i = pos; i <= n; i += (i&-i)) t[i]++;
}

int query(int pos){
    int res = 0;
    for(int i = pos; i > 0; i -= (i&-i) ) res += t[i];
    return res;
}

pair<int,int> ans[100005];

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
	freopen("IMPEVAL.inp", "r", stdin);
	freopen("IMPEVAL.out", "w", stdout);
    int n,m,p;
    cin >> n >> m >> p;
    for(int i = 1; i <= m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        e[i] = {u,v};
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    for(int i = 1; i <= n; i++) d1[i] = d2[i] = 1e18;
    Dijkstra1(); Dijkstra2();

    vector<int> vec;

    for(int i = 1; i <= n; i++){
        a[i] = {i,0,d1[i],d2[i],0};
        vec.push_back(d2[i]);
    }

    int cur = n+1;
    for(int i = 1; i <= p; i++){
        int t,w;
        cin >> t >> w;
        int u = e[t].first, v = e[t].second;
        a[cur] = {u,i, min(d1[u], d1[v]+w), min(d2[u], d2[v]+w), 0};
        cur++;
        vec.push_back(min(d2[u], d2[v]+w));
        a[cur] = {v,i, min(d1[v], d1[u]+w), min(d2[v], d2[u]+w), 1};
        vec.push_back(min(d2[v], d2[u]+w));
        cur++;
        if(min(d1[u], d1[v]+w) <=  min(d1[v], d1[u]+w) && min(d2[u], d2[v]+w) <=  min(d2[v], d2[u]+w)) ans[i].second++;
        if(min(d1[u], d1[v]+w) >=  min(d1[v], d1[u]+w) && min(d2[u], d2[v]+w) >=  min(d2[v], d2[u]+w)) ans[i].first++;

        if(min(d1[u], d1[v]+w) >=  d1[v] && min(d2[u], d2[v]+w) >= d2[v]) ans[i].first--;
        if(min(d1[v], d1[u]+w) >=  d1[u] && min(d2[v], d2[u]+w) >= d2[u]) ans[i].second--;

        if(min(d1[u], d1[v]+w) >=  d1[u] && min(d2[u], d2[v]+w) >= d2[u]) ans[i].first--;
        if(min(d1[v], d1[u]+w) >=  d1[v] && min(d2[v], d2[u]+w) >= d2[v]) ans[i].second--;
    }

    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    sort(a+1,a+cur);
    for(int i = 1; i < cur; i++){
        //cout << a[i].i << ' ' << a[i].id << ' ' << a[i].x << ' ' << a[i].y << ' ' << a[i].pos << endl;
        a[i].y = lower_bound(vec.begin(), vec.end(), a[i].y) - vec.begin() + 1;
    }

    for(int i = 1; i < cur; i++){
        if(a[i].id){
            if(a[i].pos == 0) ans[a[i].id].first += query(a[i].y);
            else ans[a[i].id].second += query(a[i].y);
        }else update(a[i].y, vec.size());
    }

    for(int i = 1; i <= p; i++){
        cout << ans[i].first+1 << ' ' << ans[i].second+1 << '\n';
    }

    return 0;
}
