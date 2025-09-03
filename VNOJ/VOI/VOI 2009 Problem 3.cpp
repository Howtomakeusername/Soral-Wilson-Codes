#include <bits/stdc++.h>

using namespace std;

int n;
int a[200005];
int b[200005];
int c[200005];
int cnt[200005];

bool Check(int i){
    if(i == 0) return false;
    if(c[i] != -1){
        if(c[i] > b[i]) return false;
        if(c[i] < b[i]) return true;
        return Check(i-1);
    }

    for(int x = 0; x < b[i]; x++) if(cnt[x]) return true;
    if(cnt[b[i]] == 0) return false;
    cnt[b[i]]--;
    bool res = Check(i-1);
    cnt[b[i]]++;
    return res;
}

bool ans = false;

void Recur(int i, int tight){
    //cout << i << ' ' << tight << ' ' << a[i] << endl;
    if(!Check(n)) return;
    if(i > n){
        ans = true;
        return;
    }

    for(int x = tight? a[i] : 0; x <= 9; x++) if(cnt[x]){
        c[i] = x;
        cnt[x]--;
        if(x > a[i]) Recur(i+1,0);
        else Recur(i+1,tight);
        if(ans) return;
        c[i] = -1;
        cnt[x]++;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("mbp.inp","r",stdin);
//    freopen("mbp.out","w",stdout);
    cin >> n;
    string sa,sb,sc;
    cin >> sa >> sb >> sc;
    string maxleft = sa > sb ? sa : sb;
    reverse(sa.begin(), sa.end());
    reverse(sb.begin(), sb.end());
    string maxright = sa < sb ? sa : sb;
    reverse(maxright.begin(), maxright.end());

    for(int i = 1; i <= n; i++) a[i] = maxleft[i-1] - '0';
    for(int i = 1; i <= n; i++) b[i] = maxright[i-1] - '0';

    //cout << maxleft << ' ' << maxright << endl;

    for(int i = 1; i <= n; i++){
        c[i] = -1;
        cnt[sc[i-1] - '0']++;
    }

    Recur(1,1);
    if(ans) for(int i = 1; i <= n; i++) cout << c[i];
    else cout << -1;
    return 0;
}
