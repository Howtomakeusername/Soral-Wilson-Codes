#include<bits/stdc++.h>

using namespace std;

#define int long long

int a[200005];

struct Query{
    int id,l,r,d;
    bool operator<(const Query& other) const{
        return d > other.d;
    }
};

const int mlog = 18;
int rmq[200005][20];

int gcd(int a, int b){
    if(a == 0) return b;
    if(b == 0) return a;
    return __gcd(a,b);
}

int range_gcd(int l, int r){
    int k = __lg(r-l+1);
    return gcd(rmq[l][k], rmq[r-(1<<k)+1][k]);
}

int fenwick[200005];
int nxt[200005];
int n,q;

inline void update(int pos, int val){
    for(; pos <= n; pos += (pos & -pos)) fenwick[pos] += val;
}

int query(int pos){
    int res = 0;
    for(; pos; pos -= (pos & -pos)) res += fenwick[pos];
    return res;
}

int ans[200005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    cin >> n >> q;
    priority_queue<pair<int,int>> pq;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        rmq[i][0] = a[i];
        pq.push({a[i],i});
        nxt[i] = i;
        update(i, nxt[i]);
    }

    for(int j = 1; j <= mlog; j++) for(int i = 1; i + (1<<j) - 1 <= n; i++) rmq[i][j] = gcd(rmq[i][j-1], rmq[i + (1<<(j-1))][j-1]);

    vector<Query> qr;
    for(int i = 1; i <= q; i++){
        int l,r,d;
        cin >> l >> r >> d;
        qr.push_back({i,l,r,d});
    }
    sort(qr.begin(), qr.end());
    int pre = 0;

    for(auto p : qr){
        if(pre != p.d){
            while(pq.size() && pq.top().first > p.d){
                int i = pq.top().second; pq.pop();
                int l = nxt[i]+1, r = n, res = n+1;
                while(r >= l){
                    int m = (r+l)/2;
                    if(range_gcd(i,m) <= p.d){
                        res = m;
                        r = m-1;
                    }else l = m+1;
                }
                if(res != n+1) pq.push({range_gcd(i,res), i});
                update(i, res-nxt[i]);
                nxt[i] = res;
            }
            if(pq.empty()) continue;
        }
        if(pq.empty()) continue;

        int pos = p.l-1;
        int l = p.l, r = p.r;

        while(r >= l){
            int m = (r+l)/2;
            if(nxt[m] <= p.r){
                pos = m;
                l = m+1;
            }else r = m-1;
        }

        ans[p.id] = (p.r+1)*(pos-p.l+1) - (query(pos) - query(p.l-1));
        pre = p.d;
    }

    for(int i = 1; i <= q; i++) cout << ans[i] << '\n';

    return 0;
}
