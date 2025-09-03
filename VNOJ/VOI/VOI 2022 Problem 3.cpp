#include<bits/stdc++.h>

using namespace std;

#define int long long
#define x first
#define y second

pair<int,int> p[100005];
int n;
int par[100005], sz[100005];

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

vector< pair<int, pair<int,int>> > e;

void manhattanMST(){
	vector<int> v(n);
	iota(v.begin(),v.end(),1);
	for(int c1 = 0; c1 <= 1; c1++){
		for(int i = 1; i <= n; i++) p[i].x *= -1;

		for(int c2 = 0; c2 <= 1; c2++){
			for(int i = 1; i <= n; i++) swap(p[i].x, p[i].y);

			sort(v.begin(),v.end(),[&](int a, int b)->bool {
                return p[a].x + p[a].y < p[b].x + p[b].y;
            });

			map<int, int> mp;
			for(auto i : v){
                pair<int,int> cur = p[i];
				for(auto id = mp.lower_bound(-cur.second); id != mp.end(); id = mp.erase(id)) {
					pair<int,int> to = p[id->second];
					int dx = cur.first - to.first;
					int dy = cur.second - to.second;
					if (dy > dx) break;

					e.push_back({dx+dy, {i, id->second}});
				}
				mp[-cur.second] = i;
			}
		}
	}

	sort(e.begin(), e.end());
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("INTERNET.inp", "r", stdin);
    freopen("INTERNET.out", "w", stdout);
    int s,k;
    cin >> n >> s >> k;
    for(int i = 1; i <= n; i++){
        cin >> p[i].x >> p[i].y;
        par[i] = i;
        sz[i] = 1;
    }
    manhattanMST();
    int ans = 0;
    for(auto pp : e){
        //cout << pp.first << ' ' << pp.second.first << ' ' << pp.second.second << endl;

        if(pp.first <= s) union_set(pp.second.first, pp.second.second);
        else if(find_set(pp.second.first) != find_set(pp.second.second)){
            ans += pp.first;
            k--;
            union_set(pp.second.first, pp.second.second);
            if(k == 0) break;
        }
    }

    cout << ans;
    return 0;
}
