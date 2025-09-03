#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9+7;

int power(int a, int b){
    if(b == 0) return 1;
    int x = power(a,b/2);
    if(b%2) return ((x*x)%mod*a)%mod;
    return (x*x)%mod;
}

int fact[1000005];
int inv[1000005];

int nCr(int n, int k){
    return ((fact[n] * inv[k])%mod * inv[n-k])%mod;
}

int l[1000005];
int pos[1000005];
int pre[1000005];
int cnt = 0;
int n,k,q;

void cal(int x){
    if(x < 1 || pos[x] == n) return;

    if(x == n){
        if(pre[x] == 0) cnt++;
        pre[x] = 1;
        return;
    }

    int y = l[pos[x]+1];
    if(y == n){
        if(pre[x] == 1) cnt--;
        pre[x] = 0;
        return;
    }

    if(pos[x+1] < pos[y+1]){
        if(pre[x] == 0) cnt++;
        pre[x] = 1;
    }else{
        if(pre[x] == 1) cnt--;
        pre[x] = 0;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("ENCODE.inp","r",stdin);
    freopen("ENCODE.out","w",stdout);

    cin >> n >> k >> q;
    fact[0] = 1;
    for(int i = 1; i <= 1e6; i++) fact[i] = (fact[i-1]*i)%mod;
    inv[1000000] = power(fact[1000000],mod-2);
    for(int i = 1e6-1; i >= 0; i--) inv[i] = (inv[i+1]*(i+1))%mod;

    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        x = n-x+1;

        pos[x] = i;
        l[i] = x;
    }

    for(int i = 1; i <= n; i++) cal(i);

    //cout << cnt << endl;
    cout << nCr(cnt+k,n) << '\n';

    while(q--){
        int i,j;
        cin >> i >> j;
        if(i > j) swap(i,j);

        if(j == n){
            if(pre[l[i]] == 1) cnt--;
            pre[l[i]] = 0;
        }
        //cout << cnt << ' ' << q << endl;

        pos[l[i]] = j;
        pos[l[j]] = i;
        swap(l[i], l[j]);

        cal(l[i]); //cout << cnt << ' ' << q << endl;
        cal(l[j]); //cout << cnt << ' ' << q << endl;
        cal(l[i]-1); //cout << cnt << ' ' << q << endl;
        cal(l[j]-1); //cout << cnt << ' ' << q << endl;

        if(pos[l[i]-1] > 1) cal(l[pos[l[i]-1]-1]);
        if(pos[l[j]-1] > 1) cal(l[pos[l[j]-1]-1]);

        if(pos[l[i]-1] > 2) cal(l[pos[l[i]-1]-2]);
        if(pos[l[j]-1] > 2) cal(l[pos[l[j]-1]-2]);

        if(pos[l[i]] > 1) cal(l[pos[l[i]]-1]);
        if(pos[l[j]] > 1) cal(l[pos[l[j]]-1]);

        if(pos[l[i]] > 2) cal(l[pos[l[i]]-2]);
        if(pos[l[j]] > 2) cal(l[pos[l[j]]-2]);


        //cout << cnt << ' ' << q << endl;
        // y+1 -> y -> x

        cout << nCr(cnt+k,n) << '\n';
    }


    return 0;
}
