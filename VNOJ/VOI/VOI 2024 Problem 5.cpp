#include <bits/stdc++.h>

#define int long long

using namespace std;

const int mod = 998244353;

vector<pair<int,int>> adj[100005];
int n;

namespace Sub1{
    int dis[100005];
    int minn[100005];

    void dfs(int v, int p){
        for(auto k : adj[v]) if(k.first != p ){
            int u = k.first, w = k.second;
            dis[u] = dis[v]+1;
            minn[u] = min(minn[v],w);
            dfs(u,v);
        }
    }

    void solve(){
        for(int i = 1; i <= n; i++){
            dis[i] = 0;
            minn[i] = 1e18;
            dfs(i,i);
            int ans = 0;
            for(int j = 1; j <= n; j++) ans += minn[j] * dis[j] * dis[j];
            cout << ans << '\n';
        }
    }
}

namespace Sub3{
    int dis[100005], dis2[100005];
    int hdis[100005], hdis2[100005];
    int sz[100005];
    int ans[100005];

    void dfs(int v, int p){
        sz[v] = 1;
        for(auto k : adj[v]) if(k.first != p){
            int u = k.first, w = k.second;
            dfs(u,v);
            sz[v] += sz[u];
            dis[v] += dis[u] + sz[u]*k.second;
            dis2[v] += dis2[u] + sz[u]*k.second*k.second + 2*dis[u]*k.second;
        }
    }

    void reroot(int v, int p){
        for(auto k : adj[v]) if(k.first != p){
            int u = k.first, w = k.second;
            int du = dis[u], dv = dis[v], du2 = dis2[u], dv2 = dis2[v], szu = sz[u], szv = sz[v];

            sz[v] -= sz[u];
            dis[v] -= dis[u] + sz[u]*k.second;
            dis2[v] -= dis2[u] + sz[u]*k.second*k.second + 2*dis[u]*k.second;

            sz[u] += sz[v];
            dis[u] += dis[v] + sz[v]*k.second;
            dis2[u] += dis2[v] + sz[v]*k.second*k.second + 2*dis[v]*k.second;

            ans[u] = dis2[u];
            reroot(u,v);

            dis[u] = du; dis[v] = dv; dis2[u] = du2; dis2[v] = dv2; sz[u] = szu; sz[v] = szv;
        }
    }

    void solve(){
        dfs(1,1);
        ans[1] = dis2[1];
        reroot(1,1);
        for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
    }
}

int ans[100005];

namespace Sub6{
    int sz[100005];
    int del[100005];
    int dis[100005];
    int minn[100005];

    void calsz(int v, int p){
        sz[v] = 1;
        for(auto k : adj[v]) if(k.first != p && !del[k.first]){
            int u = k.first, w = k.second;
            calsz(u,v);
            sz[v] += sz[u];
        }
    }

    int findcen(int v, int p, int s){
        for(auto k : adj[v]) if(k.first != p && !del[k.first]){
            int u = k.first, w = k.second;
            if(sz[u] > s/2) return findcen(u,v,s);
        }
        return v;
    }

    vector< pair<int,pair<int,int>> > vec;

    void dfs(int v, int p){
        vec.push_back({minn[v],{dis[v],v}});
        for(auto k : adj[v]) if(k.first != p && !del[k.first]){
            int u = k.first, w = k.second;
            dis[u] = dis[v]+1;
            minn[u] = min(minn[v],w);
            dfs(u,v);
        }
    }

    void dfs2(int v, int p){
        vec.push_back({minn[v],{dis[v],v}});
        for(auto k : adj[v]) if(k.first != p && !del[k.first]){
            int u = k.first, w = k.second;
            dfs2(u,v);
        }
    }

    void cal(int sign){
        vector<int> pf1, pf2, pf3;
        vector<int> sf1, sf2;
        pf1.push_back(((vec[0].first * vec[0].second.first)%mod * vec[0].second.first%mod));
        pf2.push_back(vec[0].first%mod);
        pf3.push_back((vec[0].first * vec[0].second.first)%mod);

        sf1.push_back((vec[vec.size()-1].second.first * vec[vec.size()-1].second.first)%mod);
        sf2.push_back(vec[vec.size()-1].second.first%mod);

        for(int i = 1; i < vec.size(); i++){
            pf1.push_back( (pf1.back() + ((vec[i].first * vec[i].second.first)%mod * vec[i].second.first)%mod)%mod );
            pf2.push_back( (pf2.back() + vec[i].first%mod)%mod);
            pf3.push_back( (pf3.back() + (vec[i].first * vec[i].second.first)%mod)%mod );
        }

        for(int i = vec.size()-2; i >= 0; i--){
            sf1.push_back( (sf1.back() + (vec[i].second.first * vec[i].second.first)%mod)%mod );
            sf2.push_back( (sf2.back() + vec[i].second.first%mod)%mod);
        }

        for(int i = 0; i < vec.size(); i++){
            int id = vec[i].second.second;

            //cout << vec[i].first << ' ' << vec[i].second.first << ' ' << vec[i].second.second << endl;

            if(i > 0){
                ans[id] += pf1[i-1] * sign;
                ans[id] %= mod; ans[id] += mod; ans[id] %= mod;
                //cout << pf1[i-1] * sign << endl;
                ans[id] += ((vec[i].second.first * vec[i].second.first)%mod * pf2[i-1])%mod * sign;
                ans[id] %= mod; ans[id] += mod; ans[id] %= mod;
                //cout << vec[i].second.first * vec[i].second.first << ' ' << pf2[i-1] << endl;
                //cout << (vec[i].second.first * vec[i].second.first * pf2[i-1]) * sign << endl;
                ans[id] += ((2 * vec[i].second.first)%mod * pf3[i-1])%mod * sign;
                ans[id] %= mod; ans[id] += mod; ans[id] %= mod;
                //cout << (2 * vec[i].second.first * pf3[i-1]) * sign << endl;
            }
            if(i < vec.size()-1){
                ans[id] += (sf1[vec.size()-i-2] * vec[i].first)%mod * sign;
                ans[id] %= mod; ans[id] += mod; ans[id] %= mod;
                //cout << (sf1[vec.size()-i-2] * vec[i].first) << endl;
                ans[id] += (((vec[i].second.first * vec[i].second.first)%mod * vec[i].first)%mod * (vec.size()-i-1))%mod * sign;
                ans[id] %= mod; ans[id] += mod; ans[id] %= mod;
                //cout << vec[i].second.first * vec[i].second.first << ' ' << vec[i].first << ' ' << vec.size()-i-1 << endl;
                //cout << (vec[i].second.first * vec[i].second.first * vec[i].first * (int)(vec.size()-i-1)) * sign << endl;
                ans[id] += (((2 * vec[i].second.first)%mod * vec[i].first)%mod * sf2[vec.size()-i-2])%mod * sign;
                ans[id] %= mod; ans[id] += mod; ans[id] %= mod;
                //cout << (2 * vec[i].second.first * vec[i].first * sf2[vec.size()-i-2]) * sign << endl;
            }
        }
    }

    void solve(int v){
        calsz(v,v);
        int s = sz[v];

        int r = findcen(v,v,s);
        dis[r] = 0; minn[r] = 1e9+5;
        //cout << v << ' ' << r << endl;
        dfs(r,r);
        sort(vec.begin(), vec.end());
        cal(1);
        vec.clear();

        del[r] = 1;
        for(auto k : adj[r]) if(!del[k.first]){
            dfs2(k.first,k.first);
            sort(vec.begin(), vec.end());
            //cout << k.first << ' ' << "CUR" << endl;
            cal(-1);
            vec.clear();
        }

        for(auto k : adj[r]) if(!del[k.first]) solve(k.first);
    }
}

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
    freopen("netw.inp", "r", stdin);
    freopen("netw.out", "w", stdout);
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    //Sub1::solve();
    Sub6::solve(1);
    for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
    return 0;
}
