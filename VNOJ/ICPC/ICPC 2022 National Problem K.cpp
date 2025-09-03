#include<bits/stdc++.h>

using namespace std;

bool cmp(pair<int,int> a, pair<int,int> b){
    return a.second * b.first > a.first * b.second;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    int n;
    cin >> n;
    cout << "YES" << '\n';

    vector<pair<int,int>> v;

    for(int i = 1; i*i <= 3000; i++) for(int j = ((i%2 == 0) ? 1 : 2); j < i; j += 2){
        if(__gcd(i,j) == 1){
            int x = i*i - j*j;
            int y = 2*i*j;
            v.push_back({x,y});
            v.push_back({y,x});
        }
    }

    sort(v.begin(), v.end(), cmp);
    v.erase(unique(v.begin(), v.end()));

    pair<int,int> cur = {-1e6,-1e6};
    cout << cur.first << ' ' << cur.second << '\n';
    for(int i = 1; i < n-1; i++){
        cur.first += v[i-1].first;
        cur.second += v[i-1].second;
        cout << cur.first << ' ' << cur.second << '\n';
    }

    cout << cur.first << ' ' << -1000000 << '\n';
    return 0;
}
