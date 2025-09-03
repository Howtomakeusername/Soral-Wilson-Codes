#include<bits/stdc++.h>

using namespace std;

bitset<302> a[302];
unordered_set<bitset<302>> s;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    int n,m,k;
    cin >> n >> m >> k;
    if(k == 1){
        cout << "YES";
        return 0;
    }
    for(int i = 1; i <= n; i++){
        string t;
        cin >> t;
        for(int j = 0; j < m; j++) if(t[j] == '1') a[i].set(j);
        s.insert(a[i]);
    }

    for(int i = 1; i <= n; i++) for(int j = i+1; j <= n; j++) for(int p = j+1; p <= n; p++){
        bitset<302> t = (((a[i] & a[j]) | (a[j] & a[p])) | (a[i] & a[p]));
//        cout << t[0] << ' ' << t[1] << ' ' << t[2] << '\n';
//
//        cout << a[i][0] << ' ' << a[i][1] << ' ' << a[i][2] << '\n';
//        cout << a[j][0] << ' ' << a[j][1] << ' ' << a[i][2] << '\n';
//        cout << a[j][0] << ' ' << a[i][1] << ' ' << a[i][2] << '\n';

        if(s.find(t) == s.end()){
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";
    return 0;
}
