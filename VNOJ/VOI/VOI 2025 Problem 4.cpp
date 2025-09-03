#include <bits/stdc++.h>
using namespace std;

#define int long long

int a[300005];
int pf[300005];
int ans[100005];

// |a[j] - (s+j-i)|
// |a[j]-j -(s-i)|

int getCost(int s, int i, int m){
    int c = s-i;
    int x = upper_bound(a+i,a+i+m,c)-a;
    //cout << x << ' ' << c << ' ' << "CHECK" << endl;
    return c*(x-i) - (pf[x-1] - pf[i-1]) + (pf[i+m-1] - pf[x-1] - c*(i+m-x));
}

vector<int> solve(int n, int m){
    for(int i = 1; i <= m*3; i++){
        a[i] -= i;
        pf[i] = pf[i-1]+a[i];
        //cout << a[i] << ' ' << i << endl;
    }

    ans[1] = 1e18;
    int pt = 1;
    for(int i = 1; i <= m*2+1; i++){
        int res = getCost(n+1,i,m);
        if(res < ans[1]){
            ans[1] = res;
            pt = i;
        }
        //cout << res << ' ' << i << endl;
    }

    for(int i = 2; i <= n; i++){
        ans[i] = getCost(n+i,pt,m);
        while(pt <= m*2 && getCost(n+i,pt+1,m) < ans[i]){
            pt++;
            ans[i] = getCost(n+i,pt,m);
        }
    }

    vector<int> res;
    for(int i = 1; i <= n; i++) res.push_back(ans[i]);
    return res;
}

int pfmin[100005], sfmin[100005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("cycle.inp","r",stdin);
    freopen("cycle.out","w",stdout);
    int t;
    cin >> t;
    while(t--){
        int n,m,l;
        cin >> n >> m >> l;
        vector<int> v;
        for(int i = 1; i <= m; i++){
            int x;
            cin >> x;
            v.push_back(x);
        }
        sort(v.begin(), v.end());

        for(int i = 1; i <= m; i++){
            a[i] = v[i-1];
            a[m+i] = a[i]+n;
            a[m*2+i] = a[i]+2*n;
        }

        vector<int> bm = solve(n,m);
        for(int i = 1; i <= m; i++) a[i] = 0;
        v.clear();

        for(int i = 1; i <= l; i++){
            int x;
            cin >> x;
            v.push_back(x);
        }
        sort(v.begin(), v.end());

        for(int i = 1; i <= l; i++){
            a[i] = v[i-1];
            a[l+i] = a[i]+n;
            a[l*2+i] = a[i]+2*n;
        }

        vector<int> bl = solve(n,l);
        for(int i = 1; i <= l; i++) a[i] = 0;

//        for(auto i : bm) cout << i << ' '; cout << endl;
//        for(auto i : bl) cout << i << ' '; cout << endl;
        int ans = 1e18;

        multiset<int> s;
        for(int i = l+1; i <= n-m+1; i++) s.insert(bm[i-1]);

        for(int i = 1; i <= n; i++){
            ans = min(ans, bl[i-1] + *s.begin());

            if(i <= n-l){
                auto it = s.lower_bound(bm[i+l-1]);
                s.erase(it);
            }else{
                auto it = s.lower_bound(bm[i-(n-l)-1]);
                s.erase(it);
            }

            if(i >= m) s.insert(bm[i-m]);
            if(i < m) s.insert(bm[n-m+i]);
        }

        cout << ans << '\n';
    }

    return 0;
}
