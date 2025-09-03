#include <bits/stdc++.h>

using namespace std;

int val[1005][1005];
int pf[1005][1005];
int check[1005][1005];
set<pair<int,int>> ocp[1005][1005];

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

struct State{
    int x,y,u,v,cur;
};

int a,b,c,m,n,k;

bool Next(int x, int y, int u, int v){
    if(x < 1 || x > n || y < 1 || y > m || u < 1 || u > n || v < 1 || v > m || x > u || y > v) return false;
    if(ocp[x][y].find({u,v}) == ocp[x][y].end()){
        if(pf[u][v] - pf[x-1][v] - pf[u][y-1] + pf[x-1][y-1] == 0){
            for(int i = x; i <= u; i++) for(int j = y; j <= v; j++) check[i][j] = 1;
            ocp[x][y].insert({u,v});
            return true;
        }
    }
    return false;
}

signed main(){
    ios_base::sync_with_stdio (0);
	cin.tie (0);
//    freopen("test.inp", "r", stdin);
//    freopen("test.out", "w", stdout)
    cin >> a >> b >> c >> n >> m >> k;
    for(int i = 1; i <= k; i++){
        int x,y;
        cin >> x >> y;
        val[x][y] = 1;
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) pf[i][j] = pf[i-1][j] + pf[i][j-1] - pf[i-1][j-1] + val[i][j];
    queue<State> q;
    q.push({1,1,a,b,a*b});
    Next(1,1,a,b);
    while(!q.empty()){
        auto s = q.front();
        q.pop();
        for(int i = 0; i <= 3; i++){
            if(Next(s.x + dx[i], s.y + dy[i], s.u + dx[i], s.v + dy[i])){
                q.push({s.x + dx[i], s.y + dy[i], s.u + dx[i], s.v + dy[i], s.cur});
            }
		}
        int e = (a*b*c)/s.cur;
        if(Next(s.x, s.v+1, s.u, s.v+e)) q.push({ s.x, s.v+1, s.u, s.v+e, e*(s.u-s.x+1) });
		if(Next(s.x, s.y-e, s.u, s.y-1)) q.push({ s.x, s.y-e, s.u, s.y-1, e*(s.u-s.x+1) });
		if(Next(s.u+1, s.y, s.u+e, s.v)) q.push({ s.u+1, s.y, s.u+e, s.v, e*(s.v-s.y+1) });
		if(Next(s.x-e, s.y, s.x-1, s.v)) q.push({ s.x-e, s.y, s.x-1, s.v, e*(s.v-s.y+1) });
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(check[i][j]) ans++;
    cout << ans;
    return 0;
}
