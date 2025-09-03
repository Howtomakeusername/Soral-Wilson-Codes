#include <bits/stdc++.h>

using namespace std;

char a[1005][1005];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
int vis[1005][1005][4];
map<int,pair<int,int>> mp;

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
//    freopen("test.inp", "r", stdin);
//    freopen("test.out", "w", stdout);
    int n,x,y,s;
    cin >> n >> x >> y >> s;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> a[i][j];

    if(x < 1 || x > n || y < 1){
        cout << x << ' ' << y-s;
        return 0;
    }

    if(y > n){
        int dis = min(y-n, s);
        s -= dis;
        y -= dis;

        if(a[y][x] == '#'){
            cout << x - (s+1) << ' ' << n+1;
            return 0;
        }
        if(!s) return 0;
    }

    int dir = 0, pos = 0;
    while(s && x >= 1 && y >= 1 && x <= n && y <= n){
        int nx = y + dx[dir], ny = x + dy[dir];
        while(a[nx][ny] == '#'){
            dir++; dir %= 4;
            nx = y + dx[dir], ny = x + dy[dir];
        }

        y = nx, x = ny, s--;
        if(vis[nx][ny][dir]){
            pos = vis[nx][ny][dir];
            break;
        }

        vis[nx][ny][dir] = s;
        mp[s] = {nx,ny};
    }

    if(!s){
        cout << x << ' ' << y;
        return 0;
    }

    if(pos){
        int tmp = s % (s-pos);
        pos -= tmp;
        cout << mp[pos].second << ' ' << mp[pos].first;
        return 0;
    }

    if(dir == 0) y -= s;
    if(dir == 3) x += s;
    if(dir == 2) y += s;
    if(dir == 1) x -= s;
    cout << x << ' ' << y;
    return 0;
}
