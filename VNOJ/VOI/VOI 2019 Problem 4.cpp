#include <bits/stdc++.h>

using namespace std;

#define int long long

int cnt1[100005][26];
int cnt2[100005][26];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("LIGHT.inp","r",stdin);
//    freopen("LIGHT.out","w",stdout);
    int m,m1,m2,r;
    cin >> m >> m1 >> m2 >> r;
    string s;
    cin >> s;
    string s1 = "",s2 = "";
    for(int i = 1; i <= m2; i++) s2 += s[i-1];
    for(int i = m2+1; i <= m2+m1; i++) s1 += s[i-1];

    vector<int> v1;
    vector<int> v2;
    v1.push_back(1);
    v2.push_back(2);

    int sum1 = m1, sum2 = m2;
    for(int i = 1; i <= 30; i++){
        vector<int> v;
        for(auto p : v2) v.push_back(p);
        for(auto p : v1) v.push_back(p);
        v1 = v2;
        v2 = v;
        int sum = sum1 + sum2;
        sum1 = sum2;
        sum2 = sum;
        if(sum2 >= m) break;
    }

//    for(auto i : v2) cout << i << ' ';
//    cout << endl;

    int cur = 1;
    for(auto p : v2){
        if(cur > s.size()) break;
        if(p == 1){
            int id = 1;
            int lim = cur+m1;
            for(; cur < lim; cur++){
                if(cur > s.size()) break;
                cnt1[id][s[cur-1] - 'A']++;
                //cout << id << ' ' << cur << ' ' << s[cur-1] << ' ' << 1 << endl;
                id++;
            }
            if(cur > s.size()) break;
        }else{
            int id = 1;
            int lim = cur+m2;
            for(; cur < lim; cur++){
                if(cur > s.size()) break;
                cnt2[id][s[cur-1] - 'A']++;
                //cout << id << ' ' << cur << ' ' << s[cur-1] << ' ' << 2 << endl;
                id++;
            }
            if(cur > s.size()) break;
        }
    }

    int ans = 0;
    vector<int> add;
    for(int i = 1; i <= m1; i++){
        int maxx = 1e9;
        int sum = 0;
        for(int c = 0; c < 26; c++) sum += cnt1[i][c];
        ans += sum - cnt1[i][s1[i-1] - 'A'];

        for(int c = 0; c < 26; c++) if(c != s1[i-1] - 'A'){
            //cout << cnt1[i][c] << ' ' << i << ' ' << c << ' ' << 1 << endl;
            maxx = min(sum - cnt1[i][c] - 1, maxx);
        }

        if(maxx != 1e9){
            int op = maxx - sum + cnt1[i][s1[i-1] - 'A'];
            if(op < 0) add.push_back(op);
        }
    }

    for(int i = 1; i <= m2; i++){
        int maxx = 1e9;
        int sum = 0;
        for(int c = 0; c < 26; c++) sum += cnt2[i][c];
        ans += sum - cnt2[i][s2[i-1] - 'A'];

        for(int c = 0; c < 26; c++) if(c != s2[i-1] - 'A'){
            //cout << cnt2[i][c] << ' ' << i << ' ' << c << ' ' << 2 << endl;
            maxx = min(sum - cnt2[i][c] - 1, maxx);
        }

        if(maxx != 1e9){
            int op = maxx - sum + cnt2[i][s2[i-1] - 'A'];
            if(op < 0) add.push_back(op);
        }
    }

    //cout << ans << endl;
    sort(add.begin(), add.end());
    for(int i = 0; i < min(r,(int)add.size()); i++) ans += add[i];

    cout << ans;
    return 0;
}
