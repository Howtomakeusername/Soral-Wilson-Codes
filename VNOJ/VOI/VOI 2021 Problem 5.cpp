#include <bits/stdc++.h>

using namespace std;

#define int long long

int row[1000005];
int col[1000005];

int valr[1000005];
int cntr[1000005];
int valc[1000005];
int cntc[1000005];

vector<int> dpr[40];
vector<int> dpc[40];

int dp[1000005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("connect.inp","r",stdin);
//    freopen("connect.out","w",stdout);
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++){
        int x;
        cin >> x;
        row[i] += x;
        col[j] += x;
    }

    for(int i = 1; i <= n; i++){
        valr[i] = row[i];
        if(row[i] == 0) continue;
        while(valr[i]%2==0){
            valr[i] /= 2;
            cntr[i]++;
        }
    }

    for(int i = 1; i <= m; i++){
        valc[i] = col[i];
        if(col[i] == 0) continue;
        while(valc[i]%2==0){
            valc[i] /= 2;
            cntc[i]++;
        }
    }

    for(int i = 0; i <= 38; i++) dpr[i].resize(n+5);
    for(int i = 0; i <= 38; i++) dpc[i].resize(m+5);

    for(int i = n; i >= 1; i--){
        dpr[cntr[i]][i] = i;
        //cout << dpr[cntr[i]][i] << ' ' << i << ' ' << cntr[i] << endl;
        for(int j = 1; j <= 38; j++){
            if(dpr[j-1][i]){
                if(valr[dpr[j-1][i]+1] == valr[i]) dpr[j][i] = dpr[j-1][dpr[j-1][i]+1];
            }else if(valr[i] == 0){
                if(valr[i+1] == 0 && i != n) dpr[j][i] = dpr[j][i+1];
                else dpr[j][i] = i;
            }
        }
    }

    for(int i = m; i >= 1; i--){
        dpc[cntc[i]][i] = i;
        for(int j = 1; j <= 38; j++){
            if(dpc[j-1][i]){
                if(valc[dpc[j-1][i]+1] == valc[i]) dpc[j][i] = dpc[j-1][dpc[j-1][i]+1];
            }else if(valc[i] == 0){
                if(valc[i+1] == 0 && i != m) dpc[j][i] = dpc[j][i+1];
                else dpc[j][i] = i;
            }
        }
    }

    int ans = 1;
    for(int i = n; i >= 1; i--){
        dp[i] = 1e9;
        for(int j = 0; j <= 38; j++) if(dpr[j][i]) dp[i] = min(dp[i],dp[dpr[j][i]+1]+1);
    }
    ans *= dp[1];
    memset(dp,0,sizeof(dp));
    for(int i = m; i >= 1; i--){
        dp[i] = 1e9;
        for(int j = 0; j <= 38; j++) if(dpc[j][i]) dp[i] = min(dp[i],dp[dpc[j][i]+1]+1);
    }
    ans *= dp[1];
    cout << ans;

    return 0;
}
