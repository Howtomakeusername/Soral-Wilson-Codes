#include <bits/stdc++.h>

using namespace std;

#define int short

vector<pair<int,int>> pos[1005];
int del[15][15];
char a[15][15];

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int n,m;

bool Reachable(pair<int,int> x, pair<int,int> y, pair<int,int> exc){
    for(int k = 0; k < 4; k++){
        pair<int,int> nxta = x;
        nxta.first += dx[k];
        nxta.second += dy[k];
        while(nxta.first >= 1 && nxta.first <= n && nxta.second >= 1 && nxta.second <= m){
            if(nxta == exc) return true;
            if(a[nxta.first][nxta.second] != '.' && !del[nxta.first][nxta.second]) break;
            if(nxta.first == y.first && nxta.second == y.second) return true;
            nxta.first += dx[k];
            nxta.second += dy[k];
        }
    }
    return false;
}

bool Check(pair<int,int> x, pair<int,int> y){
    for(int k = 0; k < 4; k++){
        pair<int,int> nxta = x, nxtb = y;
        int flag1 = 1, flag2 = 1;
        nxta.first += dx[k];
        nxta.second += dy[k];
        while(nxta.first >= 1 && nxta.first <= n && nxta.second >= 1 && nxta.second <= m){
            if(nxta.first == y.first && nxta.second == y.second) return true;

            if(a[nxta.first][nxta.second] != '.' && !del[nxta.first][nxta.second]){
                flag1 = 0;
                break;
            }
            nxta.first += dx[k];
            nxta.second += dy[k];
        }
        if(!flag1) continue;

        nxtb.first += dx[k];
        nxtb.second += dy[k];
        while(nxtb.first >= 1 && nxtb.first <= n && nxtb.second >= 1 && nxtb.second <= m){
            if(nxtb.first == x.first && nxtb.second == x.second) return true;

            if(a[nxtb.first][nxtb.second] != '.' && !del[nxtb.first][nxtb.second]){
                flag2 = 0;
                break;
            }
            nxtb.first += dx[k];
            nxtb.second += dy[k];
        }
        if(!flag2) continue;
        return true;
    }

    if(Reachable(x,{x.first,y.second},y) && Reachable(y,{x.first,y.second},x)) return true;
    if(Reachable(x,{y.first,x.second},y) && Reachable(y,{y.first,x.second},x)) return true;

    for(int k = 0; k < 4; k++){
        pair<int,int> z = x;
        z.first += dx[k];
        z.second += dy[k];
        while(z.first >= 1 && z.first <= n && z.second >= 1 && z.second <= m){
            if(a[z.first][z.second] != '.' && !del[z.first][z.second]) break;
            z.first += dx[k];
            z.second += dy[k];

            if(Reachable(z,{z.first,y.second},y) && Reachable(y,{z.first,y.second},z)) return true;
            if(Reachable(z,{y.first,z.second},y) && Reachable(y,{y.first,z.second},z)) return true;
        }
    }

    for(int k = 0; k < 4; k++){
        pair<int,int> z = y;
        z.first += dx[k];
        z.second += dy[k];
        while(z.first >= 1 && z.first <= n && z.second >= 1 && z.second <= m){
            if(a[z.first][z.second] != '.' && !del[z.first][z.second]) break;
            z.first += dx[k];
            z.second += dy[k];

            if(Reachable(z,{z.first,x.second},x) && Reachable(x,{z.first,x.second},z)) return true;
            if(Reachable(z,{x.first,z.second},x) && Reachable(x,{x.first,z.second},z)) return true;
        }
    }

    return false;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("mbp.inp","r",stdin);
//    freopen("mbp.out","w",stdout);
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        string s;
        cin >> s;
        for(int j = 1; j <= m; j++){
            a[i][j] = s[j-1];
            if(a[i][j] != '.') pos[(int)a[i][j]].push_back({i,j});
        }
    }

    set< pair< pair<int,int>, pair<int,int>> > v;
    for(int c = '0'; c <= '9'; c++){
        for(int i = 1; i < pos[c].size(); i++){
            for(int j = 0; j < i; j++) v.insert({pos[c][i], pos[c][j]});
        }
    }

    for(int c = 'A'; c <= 'Z'; c++){
        for(int i = 1; i < pos[c].size(); i++){
            for(int j = 0; j < i; j++) v.insert({pos[c][i], pos[c][j]});
        }
    }

    while(v.size()){
        for(auto p : v){
            if(del[p.first.first][p.first.second] || del[p.second.first][p.second.second]) continue;
            if(Check(p.first, p.second)){
                del[p.first.first][p.first.second] = 1;
                del[p.second.first][p.second.second] = 1;
            }
        }

        vector<pair< pair<int,int>, pair<int,int>>> ok;
        for(auto p : v){
            if(del[p.first.first][p.first.second] || del[p.second.first][p.second.second]){
                ok.push_back(p);
            }
        }

        if(ok.empty()) break;
        for(auto p : ok) v.erase(p);
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(del[i][j]) ans++;
    cout << ans;
    return 0;
}
