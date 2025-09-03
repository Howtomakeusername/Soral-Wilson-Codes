#include<bits/stdc++.h>

using namespace std;

#define int long long

mt19937_64 jdg(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r){
    return uniform_int_distribution<int>(l,r)(jdg);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    int n,m;
    cin >> n >> m;
    for(int i = 1; i < n; i++) cout << i << ' ' << i+1 << endl;
    int ans = n-1;
    for(int t = 1; t <= 222; t++){
        int u = rand(1,m-1), v = rand(u+1,m);
        int res = 0;
        int x;
        cout << "subtree" << ' ' << u << ' ' << v << endl;
        cin >> x;
        res += x;
        cout << "subtree" << ' ' << v << ' ' << u << endl;
        cin >> x;
        res += x;
        cout << "distance" << ' ' << u << ' ' << v << endl;
        cin >> x;
        res -= x;
        ans = max(ans, res);
    }
    cout << "! " << ans << endl;
    return 0;
}
