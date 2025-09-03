#include<bits/stdc++.h>

using namespace std;

int a[1000005];
vector<int> pos[1000005];
int ans[1000005];
int pt[1000005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    int n;
    cin >> n;

    vector<int> v;
    for(int i = 1; i <= n*n; i++){
        cin >> a[i];
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    set<pair<int,int>> s;
    for(int i = 1; i <= n*n; i++){
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        pos[a[i]].push_back(i);
    }
    for(int i = 1; i <= v.size(); i++){
        s.insert({pos[i].size(),i});
        pt[i] = 0;
    }

    for(int i = 1; i <= n; i++){
        if(s.begin()->first >= n){
            int cur = s.begin()->second;
            for(int k = pt[cur]; k < pt[cur]+n; k++){
                ans[pos[cur][k]] = i;
            }
            pt[cur] += n;

            s.erase(s.begin());
            if(pt[cur] < pos[cur].size()){
                s.insert({pos[cur].size()-pt[cur], cur});
            }
        }else{
            int cur = s.begin()->second;
            int nxt = s.rbegin()->second;
            for(int k = pt[cur]; k < pos[cur].size(); k++) ans[pos[cur][k]] = i;
            for(int k = pt[nxt]; k < pt[nxt]+n-s.begin()->first; k++) ans[pos[nxt][k]] = i;
            pt[nxt] += n-s.begin()->first;

            s.erase(s.begin());
            auto it = s.end(); it--;
            s.erase(it);
            if(pt[nxt] < pos[nxt].size()){
                s.insert({pos[nxt].size()-pt[nxt], nxt});
            }
        }
    }

    cout << "YES" << '\n';
    for(int i = 1; i <= n*n; i++) cout << ans[i] << ' ';

    return 0;
}
