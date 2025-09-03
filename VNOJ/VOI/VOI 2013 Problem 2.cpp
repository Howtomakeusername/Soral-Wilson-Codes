#include <bits/stdc++.h>

using namespace std;

string a[105];
string b[105];
int c[105];
int l[105];

int ans;
int n,m;

void Cal(int x, int y){
    int li = max(0,x), ri = min(n,n+x);
    int lj = max(0,y), rj = min(m,m+y);
    for(int j = lj; j < rj; j++) l[j] = c[j] = 0;
    if ((ri-li)*(rj-lj) <= ans) return;

    vector<int> dq(rj-lj);
    int cur = 0;
    for(int i = li; i < ri; i++){
        for (int j = lj; j < rj; j++) {
            if(a[i][j] == b[i-x][j-y]) {
                c[j]++;
                while(cur && c[dq[cur-1]] >= c[j]) cur--;
                l[j] = cur ?  dq[cur-1] : lj-1;
                dq[cur] = j; cur++;
            }else{
                c[j] = 0;
                dq[0] = j; cur = 1;
            }
        }

        cur = 0;
        int r = 1e9;
        for (int j = rj-1; j >= lj; j--) {
            if(c[j]){
                while(cur && c[dq[cur-1]] >= c[j]) cur--;
                r = cur ? dq[cur-1] : rj;

                ans = max(ans, c[j]*(r-l[j]-1));
                dq[cur] = j; cur++;
            }else{
                dq[0] = j; cur = 1;
            }
            //if(x == -1 && y == -1) cout << r << ' ' << i << ' ' << j << endl;
        }
        cur = 0;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("mbp.inp","r",stdin);
//    freopen("mbp.out","w",stdout);
    int t;
    cin >> t;
    while(t--){
        cin >> n >> m;
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];

        ans = 0;
        for (int i = -n+1; i <= n-1; i++) for (int j = -m+1; j <= m-1; j++){
            Cal(i,j);
        }
        cout << ans << '\n';
    }
    return 0;
}
