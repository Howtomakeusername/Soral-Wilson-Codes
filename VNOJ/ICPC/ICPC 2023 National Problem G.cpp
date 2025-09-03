#include <bits/stdc++.h>

using namespace std;

char a[1005][1005];
int row[1005];
int col[1005];
int checkRow[1005];
int checkCol[1005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k,p;
    while(cin >> n >> k >> p){
        if(n == 0) break;
        int placed = 0;
        int xbase = 0, ybase = 0;

        for(int i = 1; i <= n; i++){
            string s;
            cin >> s;
            for(int j = 1; j <= n; j++){
                a[i][j] = s[j-1];
                if(a[i][j] == 'R'){
                    placed++;
                    row[i]++;
                    col[j]++;
                    checkRow[i] = 1;
                    checkCol[j] = 1;
                }
            }
        }

        if(2*(placed+k) - p < 0){
            cout << "NO" << '\n';
            for(int i = 1; i <= n; i++) row[i] = col[i] = checkRow[i] = checkCol[i] = 0;
            continue;
        }

        vector<int> unvisRow, unvisCol;
        vector<int> visRow, visCol;
        for(int i = 1; i <= n; i++){
            if(!row[i]) unvisRow.push_back(i);
            else{
                xbase++;
                visRow.push_back(i);
            }
        }

        for(int i = 1; i <= n; i++){
            if(!col[i]) unvisCol.push_back(i);
            else{
                ybase++;
                visCol.push_back(i);
            }
        }

        if(k == 0){
            if(2*placed - xbase - ybase != p) cout << "NO" << '\n';
            else{
                cout << "YES" << '\n';
                for(int i = 1; i <= n; i++){
                    for(int j = 1; j <= n; j++) cout << a[i][j];
                    cout << '\n';
                }
            }
            for(int i = 1; i <= n; i++) row[i] = col[i] = checkRow[i] = checkCol[i] = 0;
            continue;
        }

        p = 2*(placed+k) - p;

        pair<int,int> res = {1e9,1e9};
        for(int x = xbase; x <= n; x++) for(int y = ybase; y <= n; y++) if((placed+k <= x*y) && (k >= max(x-xbase, y-ybase)) && (x+y == p)){
            if( (x == 0 && y > 0) || (y == 0 && x > 0)) continue;
            res = {x,y};
            break;
        }

        int x = res.first, y = res.second;
        if(x == 1e9){
            cout << "NO" << '\n';
            for(int i = 1; i <= n; i++) row[i] = col[i] = checkRow[i] = checkCol[i] = 0;
            continue;
        }
        //cout << x << ' ' << y << endl;

        vector<pair<int,int>> add;
        while(unvisCol.size() && unvisRow.size() && x > xbase && y > ybase){
            add.push_back({unvisRow.back(), unvisCol.back()});
            visCol.push_back(unvisCol.back());
            visRow.push_back(unvisRow.back());
            unvisRow.pop_back();
            unvisCol.pop_back();
            x--;
            y--;
        }

        while(x > xbase && unvisRow.size() && visCol.size()){
            add.push_back({unvisRow.back(), visCol.back()});
            unvisRow.pop_back();
            x--;
        }

        while(y > ybase && unvisCol.size() && visRow.size()){
            add.push_back({visRow.back(), unvisCol.back()});
            unvisCol.pop_back();
            y--;
        }

        for(auto pp : add){
            a[pp.first][pp.second] = 'R';
            checkRow[pp.first] = 1;
            checkCol[pp.second] = 1;
        }

        k -= add.size();
        for(int i = 1; i <= n; i++){
            if(!k) break;
            for(int j = 1; j <= n; j++) if(checkRow[i] && checkCol[j] && a[i][j] == '.'){
                a[i][j] = 'R';
                k--;
                if(!k) break;
            }
        }

        cout << "YES" << '\n';
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++) cout << a[i][j];
            cout << '\n';
        }

        for(int i = 1; i <= n; i++) row[i] = col[i] = checkRow[i] = checkCol[i] = 0;
    }

    return 0;
}
