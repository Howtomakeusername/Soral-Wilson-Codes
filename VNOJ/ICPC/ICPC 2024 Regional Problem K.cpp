#include<bits/stdc++.h>

using namespace std;

map<int,int> mp;
map<int,int> cnt;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        mp.clear();
        cnt.clear();

        vector<int> a;
        for(int i = 1; i <= n; i++){
            int x;
            cin >> x;
            a.push_back(x);
            mp[x]++;
        }

        sort(a.begin(), a.end());
        for(auto p : mp) cnt[p.second] = max(cnt[p.second], p.first);
        vector<pair<int,int>> v;
        for(auto p : cnt) v.push_back({p.second,p.first});

        sort(v.begin(), v.end(), greater<pair<int,int>>());
        pair<int,int> pre = {-1,-1};

        int ans = 2*n;

        for(auto p : v){
            if(p.first < pre.first && p.second < pre.second) continue;

            int sum = 0;
            auto it = mp.upper_bound(p.first);
            for(; it != mp.end(); it++){
                if(it->first%p.first == 0) sum += (it->first/p.first)*it->second;
                else sum += (it->first/p.first + 2)*it->second;
            }

            int x = lower_bound(a.begin(), a.end(), p.first) - a.begin();
            ans = min(ans, p.second + 2*x + sum);
            pre = p;
        }

        cout << ans << '\n';
    }
    return 0;
}
