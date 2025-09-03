#include <bits/stdc++.h>

using namespace std;

map<string, int> spe;
map<string,vector<string>> adj;
map<pair<string,string>, int> check;

map<string, int> cnt;

signed main(){
    ios_base::sync_with_stdio (0);
	cin.tie (0);
//    freopen("test.inp", "r", stdin);
//    freopen("test.out", "w", stdout)
    int n,k,s,m;
    cin >> n >> k >> s >> m;

    queue<string> q;
    for(int i = 1; i <= s; i++){
        string c;
        cin >> c;
        spe[c] = 1;
        q.push(c);
    }

    for(int i = 1; i <= m; i++){
        string x,y;
        cin >> x >> y;
        if(check.find({x,y}) != check.end()) continue;

        adj[x].push_back(y);
        adj[y].push_back(x);
        check[{x,y}] = 1;
        check[{y,x}] = 1;
    }

    while(!q.empty()){
        string u = q.front();
        q.pop();
        for(auto v : adj[u]){
            if(spe.find(v) != spe.end()) continue;
            cnt[v]++;
            if(cnt[v] == k){
                spe[v] = 1;
                q.push(v);
            }
        }
    }

    cout << spe.size() << '\n';
    for(auto c : spe) cout << c.first << ' ';
    return 0;
}
