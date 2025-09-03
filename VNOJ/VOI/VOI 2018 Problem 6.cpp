#include <bits/stdc++.h>

using namespace std;

#define int long long

int a[300005];
int res[300005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("treasure.inp","r",stdin);
//    freopen("treasure.out","w",stdout);
	int n;
	cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i] -= i;
    }

    int ans = 0;
    priority_queue<int> pq;
    for(int i = 1; i <= n; i++){
        pq.push(a[i]);
        if(pq.top() > a[i]){
            ans += pq.top() - a[i];
            pq.pop();
            pq.push(a[i]);
        }
        res[i] = pq.top();
    }

    for(int i = n-1; i >= 1; i--) res[i] = min(res[i], res[i+1]);

    cout << ans << '\n';
    for(int i = 1; i <= n; i++) cout << res[i] + i << ' ';
	return 0;
}
