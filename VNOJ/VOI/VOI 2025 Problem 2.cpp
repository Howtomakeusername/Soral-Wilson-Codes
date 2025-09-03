#include <bits/stdc++.h>
using namespace std;

#define int long long

pair<int,int> p[2005];
int len[2005];
vector<pair<int,int>> s;
//0 -> up, 1 -> stop, 2 -> down // 3 stop

int cur0 = 0, cur2 = 0;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("ROAI.inp","r",stdin);
    freopen("ROAI.out","w",stdout);
    int n,k;
    cin >> n >> k;

    int pre = 0;
    int cnt = 0;
    int sum = 0;

    for(int i = 1; i <= k; i++){
        int l,r;
        cin >> l >> r;
        if(l != pre) p[++cnt] = {pre*2,l*2}, len[cnt] = p[cnt].second-p[cnt].first;
        pre = r;
    }

    if(pre != n) p[++cnt] = {pre*2,n*2}, len[cnt] = p[cnt].second-p[cnt].first;
    k = cnt;

    for(int i = k; i >= 1; i--){
        sum += len[i];
        //cout << p[i].first << ' ' << p[i].second << ' ' << i << endl;
        s.push_back({0,2});
        s.push_back({min(n,p[i].second-p[i].first),3});

        for(int j = i-1; j >= 1; j--){
            //if(p[i].first-p[j].second > n) continue;
            s.push_back({min(n,p[i].first-p[j].second),0});
            if(len[i] >= len[j]){
                s.push_back({min(n,p[i].first-p[j].first),1});
                s.push_back({min(n,p[i].second-p[j].second),2});
            }
            else{
                s.push_back({min(n,p[i].second-p[j].second),1});
                s.push_back({min(n,p[i].first-p[j].first),2});
            }

            s.push_back({min(n,p[i].second-p[j].first), 3});
        }
    }

    sort(s.begin(), s.end());

    int ans = 0, res = sum;
    pre = 0;

    for(int i = 0; i < s.size(); ){
        res += (s[i].first-pre)*cur0;
        res -= (s[i].first-pre)*cur2;
        ans = max(ans, sum*2-res);

        //cout << cur0 << ' ' << cur2 << ' ' << s[i].first << ' ' << res << ' ' << pre << endl;

        int j = i;
        while(j < (int)s.size() && s[i].first == s[j].first){
            if(s[j].second == 0) cur0++;
            if(s[j].second == 1) cur0--;
            if(s[j].second == 2) cur2++;
            if(s[j].second == 3) cur2--;
            j++;
        }
        pre = s[i].first;
        i = j;
    }

    res += (n-pre)*cur0;
    res -= (n-pre)*cur2;
    ans = max(ans, sum*2-res);

    cout << ans;
    return 0;
}
