#include <bits/stdc++.h>

#define int long long

using namespace std;

int gcd(int a, int b, int &x, int &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b,a%b,x1,y1);
    x = y1;
    y = x1-y1*(a/b);
    return d;
}

int bx, by, g;

pair<int,int> Diophantine(int a, int b, int c){
    int t = 0;
    if(c > 1e9){
        t = (c-1e9)/b;
        c -= t*b;
    }

    int x = bx,y = by;
    int d = g;
    if(c%d) return {-1,-1};
    x *= c/d;
    y *= c/d;

    y += t;
    int p1 = b/d, p2 = a/d;
    if(x < 0){
        int m = abs(x)/p1 + (abs(x)%p1 != 0);
        x += m*p1;
        y -= m*p2;
    }

    if(y < 0){
        int m = abs(y)/p2 + (abs(y)%p2 != 0);
        x -= m*p1;
        y += m*p2;
    }

    if(x < 0 || y < 0) return {-1,-1};
    int m = x/p1;
    x -= m*p1;
    y += m*p2;
    return {x,y};
}

int a[10005];
int pf[10005];
int dp[10005];

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
    freopen("WPRO.inp", "r", stdin);
    freopen("WPRO.out", "w", stdout);
    int n,l1,l2,c,d;
    cin >> n >> l1 >> l2 >> c >> d;
    if(l1 > l2) swap(l1,l2);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) pf[i] = pf[i-1] + a[i];
    for(int i = 1; i <= n; i++) dp[i] = -1;

    g = gcd(l1,l2,bx,by);

    for(int i = 1; i <= n; i++){
        for(int j = i; j >= 1; j--) if(dp[j-1] != -1){
            if((pf[i] - pf[j-1])%g) continue;
            pair<int,int> res = Diophantine(l1,l2,pf[i] - pf[j-1]);
            if(res.first == -1) continue;

            int len = (i-j+1);
            //cout << res.first << ' ' << res.second << ' ' << pf[i] - pf[j-1] << endl;
            int sum = dp[j-1] + (len-1)*d + (res.first+res.second-1)*c;
            if(dp[i] == -1 || dp[i] > sum) dp[i] = sum;
        }
    }

    cout << dp[n];
    return 0;
}
