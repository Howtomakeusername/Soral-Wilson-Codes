#include<bits/stdc++.h>

using namespace std;

#define int long long

vector<vector<int>> a(12, vector<int>(12));
vector<vector<int>> mask(12, vector<int>(12));

void setVal(int x, int y, int val){
    for(int i = 1; i <= 9; i++) if(mask[i][y] & (1<<val)) mask[i][y] ^= (1<<val);
    for(int j = 1; j <= 9; j++) if(mask[x][j] & (1<<val)) mask[x][j] ^= (1<<val);
    int bli = (x-1)/3, blj = (y-1)/3;
    for(int i = bli*3+1; i <= (bli+1)*3; i++) for(int j = blj*3+1; j <= (blj+1)*3; j++){
        if(mask[i][j] & (1<<val)) mask[i][j] ^= (1<<val);
    }

    for(int i = x-3; i <= x+3; i++) for(int j = y-3; j <= y+3; j++) if(i >= 1 && i <= 9 && j >= 1 && j <= 9 && abs(i-x) + abs(j-y) <= 3){
        if(mask[i][j] & (1<<val)) mask[i][j] ^= (1<<val);
    }

    mask[x][y] |= (1<<val);
}

int res = 0;

void Recur(){
    if(res) return;

    int r = -1,c = -1;
    for(int i = 1; i <= 9; i++) for(int j = 1; j <= 9; j++) if(!a[i][j]){
        if(r == -1 || __builtin_popcount(mask[i][j]) <  __builtin_popcount(mask[r][c])){
            r = i;
            c = j;
        }
    }

    if(r == -1){
        res = 1;
        return;
    }

    for(int i = 0; i < 9; i++) if(mask[r][c] & (1<<i)){
        auto prea = a;
        auto premask = mask;
        a[r][c] = i+1;
        setVal(r,c,i);

        Recur();
        if(res) return;

        a = prea;
        mask = premask;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int cnt = 0;
    vector<pair<int,int>> v;

    for(int i = 1; i <= 9; i++) for(int j = 1; j <= 9; j++) mask[i][j] = (1<<9)-1;

    for(int i = 1; i <= 9; i++){
        string s;
        cin >> s;
        for(int j = 1; j <= 9; j++){
            a[i][j] = s[j-1] - '0';
            if(a[i][j] != 0){
                int x = a[i][j]-1;
                if(mask[i][j] & (1<<x)){
                    cnt++;
                    setVal(i,j,a[i][j]-1);
                    v.push_back({i,j});
                }else{
                    cout << "NO SOLUTION";
                    return 0;
                }
            }
        }
    }

    if(cnt <= 1 || a[v[0].first][v[0].second] != a[v[1].first][v[1].second]){
        Recur();
        if(!res){
            cout << "NO SOLUTION";
            return 0;
        }

        for(int i = 1; i <= 9; i++){
            for(int j = 1; j <= 9; j++) cout << a[i][j];
            cout << '\n';
        }
    }else{
        int val = a[v[0].first][v[0].second];
        set<int> s;
        for(int i = 1; i <= 9; i++) if(i != val) s.insert(i);

        for(int i = 1; i <= 9; i++) if(i != v[0].second){
            a[v[0].first][i] = *s.begin();
            setVal(v[0].first,i, a[v[0].first][i]-1);
            s.erase(s.begin());
        }

        int val2 = a[v[1].first][v[1].second]-1;
        if(mask[v[1].first][v[1].second] & (1<<val2)){
            Recur();
            if(!res){
                cout << "NO SOLUTION";
                return 0;
            }
            for(int i = 1; i <= 9; i++){
                for(int j = 1; j <= 9; j++) cout << a[i][j];
                cout << '\n';
            }
        }else{
            cout << "NO SOLUTION";
            return 0;
        }
    }
    return 0;
}
