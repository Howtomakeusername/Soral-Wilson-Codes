#include<bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

string a[22];
string b[22];
int check[22];
int dp[2000005];
int pd[2000005];
int sum[22];
vector<int> allow[22];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    while(cin >> n){
        if(n == 0) break;
        for(int i = 1; i <= n; i++){
            cin >> a[i] >> b[i];
            allow[i].clear();
        }

        for(int i = 0; i < n; i++){
            check[i] = 0;
            for(int j = 0; j < n; j++) if(a[i+1] != b[j+1] && i != j) check[i] |= (1<<j);
        }

        for(int mask = 0; mask < (1<<n); mask++) dp[mask] = pd[mask] = 0;
        dp[0] = 1;
        pd[0] = 1;

        for(int mask = 0; mask < (1<<n); mask++){
            int i = __builtin_popcount(mask);
            int rev = (1<<n)-1-mask;
            allow[i+1].push_back(mask);

            if(i < n){
                int valid = rev & check[i];
                for(; valid; valid -= (valid & -valid)) dp[mask|( (valid & -valid) )] += dp[mask];
            }

            if(n-i-1 >= 0){
                int valid = rev & check[n-i-1];
                for(; valid; valid -= (valid & -valid)) pd[mask|( (valid & -valid) )] += pd[mask];
            }
        }


        //cout << dp[(1<<n)-1] << endl;
        double total = dp[(1<<n)-1];

        for (int i = 1; i <= n; i++) {
            for(int j = 0; j < n; j++) sum[j] = 0;

    		for(int mask : allow[i]){
    		    int rev = (1<<n)-1-mask;
    			int valid = rev & check[i-1];
    			for(int j = 0; j < n; j++) if(valid & (1<<j)) sum[j] += dp[mask] * pd[rev^(1<<j)];
    		}

    		for(int j = 0; j < n; j++) cout << fixed << setprecision(8) << (double)(sum[j])/total << ' ';
    		cout << '\n';
    	}
    }
    return 0;
}
