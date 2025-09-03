#include<bits/stdc++.h>

using namespace std;

#define int long long

int getVal(char c){
    if(c == 'A') return 0;
    if(c == 'T') return 1;
    if(c == 'G') return 2;
    if(c == 'X') return 3;
}

char getChar(int c){
    if(c == 0) return 'A';
    if(c == 1) return 'T';
    if(c == 2) return 'G';
    if(c == 3) return 'X';
}

int dp[1000005][5];
int pre[5];

string s;
int n;
int ans = 1e18;

void Recur(int id, vector<int>& v){
    //cout << id << endl;
    if(id >= v.size()){
        for(int c = 0; c < 4; c++) pre[c] = 0;

        int res = 0;
        //int lst = 0;
        for(int i = 1; i <= n; i++){
            //cout << s[i-1] << ' ';
            int lst = 0;
            for(int c = 0; c < 4; c++) if(pre[c] && c != getVal(s[i-1])){
                lst = max(lst, pre[c]);
            }
            pre[getVal(s[i-1])] = i;
            res += lst;
        }
        ans = min(ans, res);
        return;
    }

    for(int c = 0; c < 4; c++){
        s[v[id]-1] = getChar(c);
        Recur(id+1, v);
        s[v[id]-1] = '?';
    }
}

void Sub1(){
    vector<int> v;
    for(int i = 1; i <= n; i++) if(s[i-1] == '?') v.push_back(i);
    Recur(0,v);
    cout << ans;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("ADN.inp", "r", stdin);
    freopen("ADN.out", "w", stdout);
    cin >> s;
    char cur = s[0];
    int lst = 1;
    n = s.size();

    if(n <= 10){
        Sub1();
        return 0;
    }

    vector< pair<pair<int,int>,char> > itv;
    for(int i = 2; i <= n; i++){
        if(s[i-1] != cur){
            itv.push_back({{lst, i-1},cur});
            lst = i;
            cur = s[i-1];
        }
    }
    itv.push_back({{lst,n}, cur});


    for(int i = 0; i < itv.size(); i++){
        auto p = itv[i];
        if(p.second == '?' && ((i == 0) || (i == itv.size()-1) || (itv[i-1].second == itv[i+1].second))){
            char c;
            if(i == 0) c = itv[i+1].second;
            else c = itv[i-1].second;
            for(int i = p.first.first; i <= p.first.second; i++) s[i-1] = c;
            //cout << i << endl;
        }
    }
    itv.clear();

    cur = s[0];
    lst = 1;
    for(int i = 2; i <= n; i++){
        if(s[i-1] != cur){
            itv.push_back({{lst, i-1},cur});
            lst = i;
            cur = s[i-1];
        }
    }
    itv.push_back({{lst,n}, cur});

    for(int i = 0; i <= itv.size(); i++) for(int c = 0; c < 4; c++) dp[i][c] = 1e18;

    if(itv[0].second == '?'){
        for(int c = 0; c < 4; c++) dp[0][c] = 0;
    }else{
        int c = getVal(itv[0].second);
        dp[0][c] = 0;
    }

    for(int i = 1; i < itv.size(); i++){
        auto p = itv[i];
        int len = p.first.second - p.first.first + 1;

        if(p.second != '?'){
            int c = getVal(p.second);
            for(int c1 = 0; c1 < 4; c1++) if(dp[i-1][c1] != 1e18){
                dp[i][c] = min(dp[i][c], dp[i-1][c1] + itv[i-1].first.second * len);
            }

            if(dp[i-1][c] != 1e18){
                if(i >= 2) dp[i][c] = min(dp[i][c], dp[i-1][c] + itv[i-2].first.second * len);
                else dp[i][c] = min(dp[i][c], dp[i-1][c]);
            }
        }else{
            for(int c = 0; c < 4; c++){
                for(int c1 = 0; c1 < 4; c1++) if(dp[i-1][c1] != 1e18){
                    dp[i][c] = min(dp[i][c], dp[i-1][c1] + itv[i-1].first.second * len);
                }

                if(dp[i-1][c] != 1e18){
                    if(i >= 2){
                        dp[i][c] = min(dp[i][c], dp[i-1][c] + itv[i-2].first.second * len);

                        if(dp[i-2][c] != 1e18){
                            if(i >= 3) dp[i][c] = min(dp[i][c], dp[i-2][c] + itv[i-3].first.second * (len+ itv[i-1].first.second - itv[i-1].first.first+1));
                            else dp[i][c] = min(dp[i][c], dp[i-2][c]);
                        }
                    }else dp[i][c] = min(dp[i][c], dp[i-1][c]);
                }
            }
        }
    }

    for(int c = 0; c < 4; c++) ans = min(ans, dp[itv.size()-1][c]);
    cout << ans;


    return 0;
}
