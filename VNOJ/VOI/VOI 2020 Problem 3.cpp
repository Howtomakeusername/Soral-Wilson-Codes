#include <bits/stdc++.h>

#define int long long

using namespace std;

struct Point{
    int x,y;
    bool operator<(const Point& other) const{
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
};

struct Line{
    int l,r,x,t;
    bool operator<(const Line& other) const{
        return x < other.x;
    }
};

vector<Line> a;
vector<int> com;
int n,d;
int val[800005], lazy[800005], t[800005];

void build(int v, int tl, int tr){
    if(tl == tr){
        val[v] = com[tl] - com[tl-1];
        t[v] = 0;
    }else{
        int tm = (tl+tr)/2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
        val[v] = val[v*2] + val[v*2+1];
        t[v] = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int add){
    if(l > tr || r < tl) return;
    if(l <= tl && tr <= r){
        lazy[v] += add;
        if(lazy[v]) t[v] = val[v];
        else if(tl != tr) t[v] = t[v*2] + t[v*2+1];
        else t[v] = 0;
        return;
    }
    int tm = (tl+tr)/2;
    update(v*2,tl,tm,l,r,add);
    update(v*2+1,tm+1,tr,l,r,add);
    if(lazy[v]) t[v] = val[v];
    else if(tl != tr) t[v] = t[v*2] + t[v*2+1];
    else t[v] = 0;
}


void Area(){
    sort(com.begin(), com.end());
    com.erase(unique(com.begin(), com.end()), com.end());
    sort(a.begin(), a.end());
    for(int i = 0; i < a.size(); i++){
        a[i].l = lower_bound(com.begin(), com.end(), a[i].l) - com.begin() + 1;
        a[i].r = lower_bound(com.begin(), com.end(), a[i].r) - com.begin();
    }

    build(1,1,com.size()-1);

    int pre = 0;
    int sum = 0;
    for(int i = 0; i < a.size(); i++){
        sum += (a[i].x - pre) * t[1];
        update(1,1,com.size()-1,a[i].l,a[i].r,a[i].t);
        pre = a[i].x;
    }
    cout << sum << endl;
}

vector<int> adj[105];
map<pair<Point,Point>,int> mp;

void DecompSeg(vector<Point>& p){
    vector<pair<pair<int,int>, int>> v;
    for(int i = 1; i <= p.size(); i++) v.push_back({{p[i-1].x, p[i-1].y},i});
    sort(v.begin(), v.end());
    for(int i = 1; i <= v.size(); i += 2){
        adj[v[i-1].second].push_back(v[i].second);
        adj[v[i].second].push_back(v[i-1].second);
    }

    int x = v[0].second;
    v.clear();

    for(int i = 1; i <= p.size(); i++) v.push_back({{p[i-1].y, p[i-1].x},i});
    sort(v.begin(), v.end());
    for(int i = 1; i <= v.size(); i += 2){
        adj[v[i-1].second].push_back(v[i].second);
        adj[v[i].second].push_back(v[i-1].second);
    }

    mp.clear();
    int u = x;
    int pre = 0;
    do{
        int nxt = 0;
        for(int v : adj[u]) if(v != pre){
            nxt = v;
            break;
        }

        int res = -1;
        if (p[u-1].y < p[nxt-1].y) res = 1;

        mp[{p[u-1], p[nxt-1]}] = res;
        mp[{p[nxt-1], p[u-1]}] = res;
        pre = u;
        u = nxt;
        if(mp.size() > p.size()*2) break;
    }while(u != x);

    for(int i = 1; i <= p.size(); i++) adj[i].clear();
}

void Split(int l, int r, vector<pair<int, int>> &ans, set<int> &s){
    if(l == r) return;
    auto it = s.upper_bound(l);
    int last = l;
    while (*it != r){
        ans.push_back({last, *it});
        last = *it;
        ++it;
    }
    ans.push_back({last, r});
}

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
//    freopen("test.inp", "r", stdin);
//    freopen("test.out", "w", stdout)
    cin >> n >> d;
    for(int i = 1; i <= n; i++){
        int g,r;
        cin >> g >> r;
        r *= d; r %= 360;
        vector<Point> p;
        for(int j = 1; j <= g; j++){
            int x,y;
            cin >> x >> y;
            p.push_back({x,y});
        }

        while(r){
            Point root = p[0];
            for (int i = 1; i < p.size(); i++) {
                //tro ve goc (0,0)
                p[i].x -= root.x;
                p[i].y -= root.y;
                //xoay 90 do
                p[i] = {p[i].y, -p[i].x};
                //tro ve goc (x,y)
                p[i].x += root.x;
                p[i].y += root.y;
            }
            r -= 90;
        }

        sort(p.begin(), p.end());
        DecompSeg(p);

        set<int> s;
        for(auto i : p) s.insert(i.y);

        for (int i = 1; i <= p.size(); i += 2) {
            vector<pair<int,int>> minn;
            Split(p[i-1].y, p[i].y, minn, s);

            int sign = mp[{p[i-1], p[i]}];
            for (auto pp : minn){
                //cout << p[i-1].x << ' ' << pp.first << ' ' << pp.second << ' ' << sign << endl;
                a.push_back({pp.first, pp.second,p[i-1].x,sign});
                com.push_back(pp.first);
                com.push_back(pp.second);
            }
        }
    }

    Area();
    return 0;
}
