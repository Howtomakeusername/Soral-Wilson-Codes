#include<bits/stdc++.h>

using namespace std;

string s[1005];
int ans[1005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) s[0] += '0';
    cout << "? " << s[0] << endl;
    int res;
    cin >> res;
    if(res == 0) for(int i = 1; i <= n; i++) s[0][i-1] = '1';

    for(int i = 1; i <= n; i++){
        s[i] = s[i-1];
        s[i][i-1] = char(((s[i][i-1] - '0') ^ 1) + '0') ;
        //cout << s[i] << endl;
    }

    int l = 0, r = n;
    while(l + 1 < r){
        int m = (r+l)/2;
        cout << "? " << s[m] << endl;
        cin >> res;
        if(res == 1) l = m;
        else r = m;
    }

    string t = s[l];
    for(int i = 1; i <= n; i++){
        int bit = t[i-1] - '0';

        t[i-1] = char(((t[i-1] - '0') ^ 1) + '0') ;
        cout << "? " << t << endl;
        cin >> res;
        t[i-1] = char(((t[i-1] - '0') ^ 1) + '0') ;

        if(res == 0) ans[i] = bit^1;
        else ans[i] = bit;
    }

    cout << "! ";
    for(int i = 1; i <= n; i++) cout << ans[i];
    cout << endl;

    return 0;
}
