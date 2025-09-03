#include<bits/stdc++.h>

using namespace std;

int a[2005];
vector<pair<int,int>> pos[4000005];
vector<int> v;
int n,d;

namespace Sub1{
    void solve(){
        int ans = 0;

        for(int mask = 1; mask < (1<<n); mask++) if(__builtin_popcount(mask)%2 == 0){
            vector<int> vec;
            for(int i = 0; i < n; i++) if(mask & (1<<i)){
                vec.push_back(a[i+1]);
            }

            int maxx = 0, minn = 2e9;
            for(int i = 0; i < vec.size()/2; i++){
                maxx = max(maxx, vec[i] + vec[vec.size()-i-1]);
                minn = min(minn, vec[i] + vec[vec.size()-i-1]);
            }

            if(maxx - minn <= d) ans = max(ans, (int)vec.size()/2);
        }

        cout << ans;
    }
}

namespace Sub4{
    int chose[2005];
    int ans = 0;

    bool cmp(pair<int,int> p1, pair<int,int> p2){
        if(p1.second != p2.second) return p1.second > p2.second;
        return p1.first < p2.first;
    }

    void solve(){
        for(int v1 = 1; v1 <= v.size(); v1++){
            vector<pair<int,int>> pp;
            for(auto p : pos[v1]){
                pp.push_back(p);
                chose[p.first] = 0;
                chose[p.second] = 0;
            }

            if(d == 1){
                if(v1 < v.size() && v[v1] == v[v1-1]+1){
                    for(auto p : pos[v1+1]){
                        pp.push_back(p);
                        chose[p.first] = 0;
                        chose[p.second] = 0;
                    }
                }
            }

            sort(pp.begin(), pp.end(), cmp);

            int res = 0;
            for(auto p : pp){
                if(!chose[p.first] && !chose[p.second]){
                    //cout << p.first << ' ' << p.second << ' ' << v[v1-1] << endl;
                    chose[p.first] = 1;
                    chose[p.second] = 1;
                    res++;
                }
            }

            ans = max(ans, res);
        }

        cout << ans;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("PAIR.inp", "r", stdin);
    freopen("PAIR.out", "w", stdout);

    cin >> n >> d;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a+1, a+1+n);


    for(int i = 1; i <= n; i++) for(int j = i+1; j <= n; j++){
        v.push_back(a[i] + a[j]);
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 1; i <= n; i++) for(int j = i+1; j <= n; j++){
        int x = a[i]+a[j];
        int p = lower_bound(v.begin(), v.end(),x) - v.begin()+1;
        pos[p].push_back({i,j});
    }

    if(n <= 10) Sub1::solve();
    else Sub4::solve();

    return 0;
}
