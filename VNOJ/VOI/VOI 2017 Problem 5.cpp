#include <bits/stdc++.h>

using namespace std;

__int128_t dp[52][51][33];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("mbp.inp","r",stdin);
//    freopen("mbp.out","w",stdout);
    int n,k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());

    __int128_t cur = 0;
    for(auto d : t){
        cur = cur*10 + (d-48);
    }

    for(int j = k+1; j <= n; j++) for(int mask = 0; mask < (1<<s.size()); mask++){
        if(__builtin_popcount(mask) <= 1) dp[n+1][j][mask] = 1;
    }

    for(int i = n; i >= 1; i--){
        for(int j = 0; j <= n; j++){
            for(int mask = 0; mask < (1<<s.size()); mask++){
                for(int c = 0; c < s.size(); c++){
                    if( (__builtin_popcount(mask^(1<<c)) <= 1) && (i > 1)) dp[i][j][mask] += dp[i+1][j+1][mask^(1<<c)];
                    else dp[i][j][mask] += dp[i+1][j][mask^(1<<c)];
                }
            }
        }
    }

    cur--;
    int j = 0, mask = 0;
    for(int i = 1; i <= n; i++){
        for(int c = 0; c < s.size(); c++){
            __int128_t nxt;

            if( (__builtin_popcount(mask^(1<<c)) <= 1) && (i > 1)){
                nxt = dp[i+1][j+1][mask^(1<<c)];
                if (cur >= nxt) cur -= nxt;
                else{
                    cout << s[c];
                    mask ^= (1<<c);
                    j++;
                    break;
                }
            }else{
                nxt = dp[i+1][j][mask^(1<<c)];
                if (cur >= nxt) cur -= nxt;
                else{
                    cout << s[c];
                    mask ^= (1<<c);
                    break;
                }
            }
        }
    }
    return 0;
}
