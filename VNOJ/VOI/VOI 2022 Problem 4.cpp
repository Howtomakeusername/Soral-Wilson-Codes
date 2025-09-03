#include <bits/stdc++.h>

using namespace std;

#define int long long

pair<int,int> p[100005];
int w[100005];
int t[800005], lazy[800005];
vector<pair<int,int>> itv[800005];

void push(int v, int tl, int tr){
    if(lazy[v]){
        t[v] += lazy[v];
        if(tl != tr){
            lazy[v*2] += lazy[v];
            lazy[v*2+1] += lazy[v];
        }
        lazy[v] = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int val){
    push(v,tl,tr);
    if(l > tr || r < tl) return;
    if(l <= tl && tr <= r){
        //cout << tl << ' ' << tr << ' ' << l << ' ' << r << ' ' << val << endl;
        lazy[v] += val;
        push(v,tl,tr);
        return;
    }
    int tm = (tl+tr)/2;
    update(v*2,tl,tm,l,r,val);
    update(v*2+1,tm+1,tr,l,r,val);
    t[v] = max(t[v*2], t[v*2+1]);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("SSEQ.inp", "r", stdin);
    freopen("SSEQ.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> v;
    for(int i = 1; i <= n; i++){
        cin >> p[i].first >> p[i].second >> w[i];
        v.push_back(p[i].first);
        v.push_back(p[i].second);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 1; i <= n; i++){
        p[i].first = lower_bound(v.begin(), v.end(), p[i].first) - v.begin() + 1;
        p[i].second = lower_bound(v.begin(), v.end(), p[i].second) - v.begin() + 1;
        itv[p[i].second].push_back({p[i].first, w[i]});
    }

    int ans = 0;
    for(int i = 1; i <= v.size(); i++){
        for(auto p : itv[i]) update(1,1,v.size(),1,p.first,p.second);


        push(1,1,v.size());
        ans = max(ans, t[1]);
    }

    cout << ans;
    return 0;
}
