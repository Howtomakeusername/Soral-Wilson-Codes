#include <bits/stdc++.h>

using namespace std;

#define int long long

const int mod = 1e9+7;

int fact[100005];
int invmod[100005];
int invfact[100005];

int req[100005];
string a[100005];
int cnt[55][30];
int chose[55][30];

int nPr(int n, int r){
    return (fact[n] * invfact[n-r])%mod;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("connect.inp","r",stdin);
//    freopen("connect.out","w",stdout);
    fact[0] = 1;
    for(int i = 1; i <= 1e5; i++) fact[i] = (fact[i-1]*i)%mod;
    invmod[1] = 1;
    for(int i = 2; i <= 1e5; i++) invmod[i] = mod - (mod/i * invmod[mod%i])%mod;
    invfact[0] = 1;
    for(int i = 1; i <= 1e5; i++) invfact[i] = (invfact[i-1] * invmod[i])%mod;

    int t;
    cin >> t;
    while(t--){
        memset(cnt,0,sizeof(cnt));
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++) cin >> req[i];
        int d;
        cin >> d;
        vector<int> v;
        for(int i = 1; i <= d; i++){
            cin >> a[i];
            cnt[a[i].size()][a[i][0] - 'a']++;
            if(a[i].size() == n) v.push_back(i);
        }

        if(v.empty()){
            cout << 0 << '\n';
            continue;
        }

        int ans = 0;
        for(auto i : v){
            set<pair<int,int>> s;
            cnt[a[i].size()][a[i][0] - 'a']--;

            for(int j = 1; j <= n; j++){
                int c = a[i][j-1] - 'a';
                chose[req[j]][c]++;
                s.insert({req[j],c});
            }

            int flag = 1;
            for(auto p : s){
                if(cnt[p.first][p.second] < chose[p.first][p.second]){
                    flag = 0;
                    break;
                }
            }

            if(!flag){
                cnt[a[i].size()][a[i][0] - 'a']++;
                memset(chose,0,sizeof(chose));
                continue;
            }

            int res = 1;
            for(auto p : s){
                res *= nPr(cnt[p.first][p.second], chose[p.first][p.second]);
                res %= mod;
            }

            ans += res;
            ans %= mod;
            cnt[a[i].size()][a[i][0] - 'a']++;
            memset(chose,0,sizeof(chose));
        }
        cout << ans << '\n';
    }
    return 0;
}
