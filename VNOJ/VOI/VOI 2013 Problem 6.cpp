#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ULL unsigned long long
const ULL BASE = 1000000000;
typedef vector<ULL> BigInt;

void println(const BigInt& a) {
    int L = a.size();
    printf("%llu", a[L - 1]);
    for (int i = L - 2; i >= 0; i--) printf("%09llu", a[i]);
    printf("\n");
}
BigInt operator + (const BigInt& a, const BigInt& b) {
    BigInt c; ULL carry = 0;
    for (size_t i = 0; i < a.size() || i < b.size(); i++) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        c.push_back(carry % BASE); carry /= BASE;
    }
    if (carry) c.push_back(carry);
    return c;
}
BigInt operator * (const BigInt& a, const int mul) {
    BigInt c; ULL carry = 0;
    for (size_t i = 0; i < a.size(); i++) {
        carry += a[i] * mul; c.push_back(carry % BASE); carry /= BASE;
    }
    if (carry) c.push_back(carry);
    return c;
}
bool operator < (const BigInt& a, const BigInt& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] < b[i];
    return false;
}


int a[205];
BigInt cnt[205][205];
BigInt dp[205][205];
int check[205][205];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("mbp.inp","r",stdin);
//    freopen("mbp.out","w",stdout);
    for(int i = 0; i <= 200; i++) cnt[i][0] = {1};
    for(int i = 1; i <= 200; i++) for(int j = 1; j < i; j++){
        cnt[i][j] = cnt[i-1][j] * (j+1) + cnt[i-1][j-1] * (i-j);
        //if(i == 2) cout << cnt[i][j] << ' ' << i << ' ' << j << endl;
    }

    for(int i = 1; i <= 200; i++) for(int j = 1; j <= 200; j++){
        cnt[i][j] = cnt[i][j]+ cnt[i][j-1];
    }

    int t;
    cin >> t;
    while(t--){
        int n, s, w, m, bmin, bmax;
        cin >> n >> s >> w >> m >> bmin >> bmax;
        for(int i = 1; i <= n; i++) cin >> a[i], a[i] *= m;
        check[0][0] = 1;
        for(int i = 1; i <= n; i++) for(int j = 1; j <= s; j++){
            int sum = 0;
            for(int k = i-1; k >= 0; k--){
                sum += a[k+1];
                if(sum > bmax) break;
                if(sum >= bmin && check[k][j-1]){
                    check[i][j] = 1;
                    if(dp[i][j] < dp[k][j-1] + cnt[i-k][w]) dp[i][j] = dp[k][j-1] + cnt[i-k][w];
                }
            }
        }

        println(dp[n][s]);

        for(int i = 0; i <= n; i++) for(int j = 0; j <= s; j++){
            check[i][j] = 0;
            dp[i][j] = {0};
        }
    }

    return 0;
}
