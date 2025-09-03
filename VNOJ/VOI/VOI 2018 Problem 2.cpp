#include <bits/stdc++.h>

using namespace std;

pair<int,int> p[50005];
int n,m;

bool Check(int lim){
    vector<pair<int,int>> v;
    for(int i = 1; i <= lim; i++) v.push_back(p[i]);
    sort(v.begin(), v.end());

    int j = 0;
    multiset<int> s;
    for(int i = 1; i <= m; i++){
        while(v[j].first == i && (j < lim)){
            s.insert(v[j].second);
            j++;
        }

        if(s.empty()) continue;

        if(*s.begin() < i) return false;
        else s.erase(s.begin());
    }

    return s.empty();
}

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
//    freopen("test.inp", "r", stdin);
//    freopen("test.out", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        cin >> m >> n;
        for(int i = 1; i <= n; i++) cin >> p[i].first >> p[i].second;
        int l = 1, r = n, res = 1;
        while(r >= l){
            int mid = (r+l)/2;
            //cout << l << ' ' << r << ' ' << mid << endl;
            if(Check(mid)){
                res = mid;
                l = mid+1;
            }else r = mid-1;
        }
        cout << res << '\n';
    }
    return 0;
}
