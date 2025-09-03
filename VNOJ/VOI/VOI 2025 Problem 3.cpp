#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9+7;

inline void addmod(int &a, int b){
    a += b;
    if(a >= mod) a -= mod;
}

string L, R;
int type;

namespace Sub1{
    int dp[1005][20][7];

    int cal(int id, int cur, int pre, int tight){
        if(id < 0) return ((cur == 17) && (pre != 5));

        if(!tight && dp[id][cur][pre] != -1) return dp[id][cur][pre];
        int lim = 0;

        if(type) lim = (tight ? R[(int)R.size()-1-id]-'0' : 9);
        else lim = (tight ? L[(int)L.size()-1-id]-'0' : 9);

        int res = 0;
        for(int i = 0; i <= lim; i++) if(pre == 5 || (i + pre) % 5){
            int new_tight = (tight && (i == lim));
            int new_pre = pre;
            if(pre != 5 || i != 0) new_pre = i % 5;

            if(cur == 16){
                // f = 16
                addmod(res, cal(id-1, 16, new_pre, new_tight));
                if(new_pre != 5){
                    // f = i
                    addmod(res, cal(id-1, i, new_pre, new_tight));
                    // f = 17 if i == 0 at start of XOR (equivalent to new_cur==0)
                    if(i == 0) addmod(res, cal(id-1, 17, new_pre, new_tight));
                }
            }else if(cur == 17){
                // absorbing
                addmod(res, cal(id-1, 17, new_pre, new_tight));
            }else{
                int new_cur = cur ^ i;
                // f = new_cur
                addmod(res, cal(id-1, new_cur, new_pre, new_tight));
                // can jump to 17 when XOR hits 0
                if(new_cur == 0) addmod(res, cal(id-1, 17, new_pre, new_tight));
            }
        }

        if(!tight) dp[id][cur][pre] = res;
        return res;
    }

    int solve(){
        if(type) return cal((int)R.size()-1, 16, 5, 1);
        return cal((int)L.size()-1, 16, 5, 1);
    }

    void init(){
        memset(dp, -1, sizeof(dp));
    }
}

namespace Sub2{
    int cal(int id, int cur, int cur2, int pre, int tight);
    int dp[1005][20][20][7];
    vector<int> d;

    // helper to combine a fixed f with all possible g (from cur2)
    inline void combineG(int &res, int id, int fval, int cur2, int i, int new_pre, int new_tight){
        int x,y;
        if(cur2 == 16){
            x = fval, y = 16;
            if(x > y) swap(x,y);

            addmod(res, cal(id-1, x,y, new_pre, new_tight));
            if(new_pre != 5){
                x = fval, y = i;
                if(x > y) swap(x,y);
                // g = i
                addmod(res, cal(id-1, x, y, new_pre, new_tight));
                // g = 17 if i == 0 at start of XOR
                if(i == 0){
                    x = fval, y = 17;
                    if(x > y) swap(x,y);
                    addmod(res, cal(id-1, fval, 17, new_pre, new_tight));
                }
            }
        }else if(cur2 == 17){
            // absorbing
            x = fval, y = 17;
            if(x > y) swap(x,y);
            addmod(res, cal(id-1, x, y, new_pre, new_tight));
        }else{
            int new_cur2 = cur2 ^ i;
            x = fval, y = new_cur2;
            if(x > y) swap(x,y);
            // g = new_cur2
            addmod(res, cal(id-1, fval, new_cur2, new_pre, new_tight));
            // g = 17 when XOR hits 0
            if(new_cur2 == 0){
                x = fval, y = 17;
                if(x > y) swap(x,y);
                addmod(res, cal(id-1, fval, 17, new_pre, new_tight));
            }
        }
    }

    int cal(int id, int cur, int cur2, int pre, int tight){
        if(id < 0) return ((cur == 17) && (cur2 == 17) && (pre != 5));

        if(!tight && dp[id][cur][cur2][pre] != -1) return dp[id][cur][cur2][pre];
        int lim = 0;

        if(type) lim = (tight ? R[(int)R.size()-1-id]-'0' : 9);
        else lim = (tight ? L[(int)L.size()-1-id]-'0' : 9);

        int res = 0;
        for(int i = 0; i <= lim; i++) if(pre == 5 || (i + pre) % 5){
            int new_tight = (tight && (i == lim));
            int new_pre = pre;
            if(pre != 5 || i != 0) new_pre = i % 5;

            if(cur == 16){
                // f = 16
                combineG(res, id, 16, cur2, i, new_pre, new_tight);
                if(new_pre != 5){
                    // f = i
                    combineG(res, id, i, cur2, i, new_pre, new_tight);
                    // f = 17 if i == 0 at start of XOR
                    if(i == 0) combineG(res, id, 17, cur2, i, new_pre, new_tight);
                }
            }else if(cur == 17){
                // f = 17 (absorbing)
                combineG(res, id, 17, cur2, i, new_pre, new_tight);
            }else{
                int new_cur = cur ^ i;
                // f = new_cur
                combineG(res, id, new_cur, cur2, i, new_pre, new_tight);
                // f = 17 when XOR hits 0
                if(new_cur == 0) combineG(res, id, 17, cur2, i, new_pre, new_tight);
            }
        }

        if(!tight) dp[id][cur][cur2][pre] = res;
        return res;
    }

    int solve(){
        if(type) return cal((int)R.size()-1, 16, 16, 5, 1);
        return cal((int)L.size()-1, 16, 16, 5, 1);
    }

    void init(){
        memset(dp, -1, sizeof(dp));
    }
}

namespace Sub3{
    int cal(int id, int cur, int cur2, int pre, int tight);
    int dp[1005][20][20][7][2];
    vector<int> d;
    int maxx = 0;

    // helper to combine a fixed f with all possible g (from cur2)
    inline void combineG(int &res, int id, int fval, int cur2, int i, int new_pre, int new_tight){
        int x,y;
        if(cur2 == 16){
            x = fval, y = 16;
            if(x > y) swap(x,y);

            addmod(res, cal(id-1, x,y, new_pre, new_tight));
            if(new_pre != 5){
                x = fval, y = i;
                if(x > y) swap(x,y);
                // g = i
                addmod(res, cal(id-1, x, y, new_pre, new_tight));
                // g = 17 if i == 0 at start of XOR
                if(i == 0){
                    x = fval, y = 17;
                    if(x > y) swap(x,y);
                    addmod(res, cal(id-1, fval, 17, new_pre, new_tight));
                }
            }
        }else if(cur2 == 17){
            // absorbing
            x = fval, y = 17;
            if(x > y) swap(x,y);
            addmod(res, cal(id-1, x, y, new_pre, new_tight));
        }else{
            int new_cur2 = cur2 ^ i;
            x = fval, y = new_cur2;
            if(x > y) swap(x,y);
            // g = new_cur2
            addmod(res, cal(id-1, fval, new_cur2, new_pre, new_tight));
            // g = 17 when XOR hits 0
            if(new_cur2 == 0){
                x = fval, y = 17;
                if(x > y) swap(x,y);
                addmod(res, cal(id-1, fval, 17, new_pre, new_tight));
            }
        }
    }

    int cal(int id, int cur, int cur2, int pre, int tight){
        //cout << id << endl;
        if(id < 0) return ((cur == 17) && (cur2 == 17) && (pre != 5));

        if(dp[id][cur][cur2][pre][tight] != -1) return dp[id][cur][cur2][pre][tight];
        int lim = 0;

        lim = (tight ? R[(int)R.size()-1-id]-'0' : 9);

        int res = 0;
        for(int i = 0; i <= lim; i++) if(pre == 5 || (i + pre) % 5){
            int new_tight = (tight && (i == lim));
            int new_pre = pre;
            if(pre != 5 || i != 0) new_pre = i % 5;

            if(cur == 16){
                // f = 16
                combineG(res, id, 16, cur2, i, new_pre, new_tight);
                if(new_pre != 5){
                    // f = i
                    combineG(res, id, i, cur2, i, new_pre, new_tight);
                    // f = 17 if i == 0 at start of XOR
                    if(i == 0) combineG(res, id, 17, cur2, i, new_pre, new_tight);
                }
            }else if(cur == 17){
                // f = 17 (absorbing)
                combineG(res, id, 17, cur2, i, new_pre, new_tight);
            }else{
                int new_cur = cur ^ i;
                // f = new_cur
                combineG(res, id, new_cur, cur2, i, new_pre, new_tight);
                // f = 17 when XOR hits 0
                if(new_cur == 0) combineG(res, id, 17, cur2, i, new_pre, new_tight);
            }
        }

        dp[id][cur][cur2][pre][tight] = res;
        return res;
    }

    int solve(){
        return cal((int)R.size()-1, 16, 16, 5, 1);
    }

    void init(){
        memset(dp, -1, sizeof(dp));
    }
}

map<pair<string,string>,int> mp;

int cnt[16];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//
    freopen("pnum.inp","r",stdin);
    freopen("pnum.out","w",stdout);

    int k; cin >> k;
    if(k == 1) Sub1::init();
    else Sub2::init();

    int pre = 0;
    Sub3::init();
    string tmp = "1";
    type = 1;
    for(int i = 1; i <= 999; i++){
        R += '9';
        int cur = Sub3::solve();
        mp[{tmp,R}] = (cur-pre+mod)%mod;
        pre = cur;
        tmp += '0';
    }


    int t; cin >> t;
    while(t--){
        cin >> L >> R;
        if(mp.find({L,R}) != mp.end()){
            cout << mp[{L,R}] << '\n';
            continue;
        }

        memset(cnt,0,sizeof(cnt));
        cnt[0] = 1;
        long long add = 0;
        int cur = 0;

        for(int i = 0; i < L.size(); i++){
            cur ^= (L[i] - '0');
            add += cnt[cur];
            cnt[cur]++;

            if(i >= 1 && ((L[i] - '0') + (L[i-1] - '0'))%5 == 0){
                add = 0;
                break;
            }
        }

        if(k == 1){
            type = 1;
            int ansR = Sub1::solve();
            type = 0;
            int ansL = Sub1::solve();
            cout << (ansR-ansL+mod+add) % mod << '\n';
        }
        else{
            add *= add;

            type = 1;
            int ansR = Sub2::solve();
            type = 0;
            int ansL = Sub2::solve();
            cout << (ansR-ansL+mod+add) % mod << '\n';
        }
    }
    return 0;
}
