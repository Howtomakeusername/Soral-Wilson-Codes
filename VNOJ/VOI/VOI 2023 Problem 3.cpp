#include <bits/stdc++.h>

using namespace std;

pair<int,int> a[50005];
pair<int,int> qr[100005];
int le[200005], ri[200005];

int check[20][200005];
int cnt[200005];

int dp[20][200005][20];
long long mask[20][200005];
int curmax[200005];

int w,l,n,q;
vector<int> v;

void updateCol(int c, int r){
    for(int j = le[c]; j <= ri[c]; j++){
        for(int k = 1; k <= w; k++){
            int dis = abs(r-k) + abs(v[c-1] - v[j-1]);
            if(dis < w){
                dp[k][j][dis]++;
                mask[k][j] |= (1LL<<dis);
            }
        }
    }
}

void removeCol(int c, int r){
    for(int j = le[c]; j <= ri[c]; j++){
        for(int k = 1; k <= w; k++){
            int dis = abs(r-k) + abs(v[c-1] - v[j-1]);
            if(dis < w){
                dp[k][j][dis]--;
                if(dp[k][j][dis] < 0){
                    while(true) cout << 1;
                }

                if(!dp[k][j][dis]){
                    mask[k][j] ^= (1LL<<dis);
                }
            }
            //cout << dis << ' ' << k << ' ' << v[j-1] << ' ' << v[c-1] << endl;
        }
    }
}

int checkLeft(int c){
    int maxx = 0;
    for(int i = 1; i <= w; i++){
        if(mask[i][c] == 0){
            while(true) cout << 1;
        }
        maxx = max(maxx, __builtin_ctzll(mask[i][c]));
        //cout << i << ' ' << maxx << endl;
    }
    return maxx+(v[c-1]-1);
}

int checkRight(int c){
    int maxx = 0;
    for(int i = 1; i <= w; i++){
        if(mask[i][c] == 0){
            while(true) cout << 1;
        }
        maxx = max(maxx, __builtin_ctzll(mask[i][c]));
    }
    return maxx+(l-v[c-1]);
}

int solveTwo(int c1, int c2){
    int l = (v[c2-1]-v[c1-1])/2, r = (v[c2-1]-v[c1-1])/2+w+1;
    int res = 0;
    while(r >= l){
        int mid = (r+l)/2;
        int flag = 1;

        for(int i = 1; i <= w; i++){
            if(mask[i][c1] == 0){
                while(true) cout << 1;
            }
            if(mask[i][c2] == 0){
                while(true) cout << 1;
            }


            int ml = __builtin_ctzll(mask[i][c1]);
            int mr = __builtin_ctzll(mask[i][c2]);

            if( (max(0, mid - ml + 1) + max(0, mid - mr + 1)) < (v[c2-1]-v[c1-1]+1)){
                flag = 0;
                break;
            }
        }
        if(flag){
            res = mid;
            r = mid-1;
        }else l = mid+1;
    }
    //cout << "SOLVE2" << ' ' << c1 << ' ' << c2 << endl;
    return res;
}

signed main() {
    ios_base::sync_with_stdio (0);
	cin.tie (0);
    freopen("ROBOT.inp", "r", stdin);
    freopen("ROBOT.out", "w", stdout);
    cin >> w >> l >> n >> q;

    for(int i = 1; i <= n; i++){
        cin >> a[i].first >> a[i].second;
        v.push_back(a[i].second);
    }

    for(int i = 1; i <= q; i++){
        cin >> qr[i].first >> qr[i].second;
        v.push_back(qr[i].second);
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 1; i <= n; i++){
        int x = a[i].second;
        a[i].second = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
        le[a[i].second] = lower_bound(v.begin(), v.end(), x-w) - v.begin() + 1;
        ri[a[i].second] = upper_bound(v.begin(), v.end(), x+w) - v.begin();
    }

    for(int i = 1; i <= q; i++){
        int x = qr[i].second;
        qr[i].second = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
        le[qr[i].second] = lower_bound(v.begin(), v.end(), x-w) - v.begin() + 1;
        ri[qr[i].second] = upper_bound(v.begin(), v.end(), x+w) - v.begin();
    }

    set<int> col;
    for(int i = 1; i <= n; i++){
        check[a[i].first][a[i].second] = 1;
        cnt[a[i].second]++;
        col.insert(a[i].second);
    }

    for(int i = 1; i <= n; i++){
        updateCol(a[i].second, a[i].first);
    }

    set<pair<int,int>> dis;
    curmax[*col.begin()] = checkLeft(*col.begin());
    dis.insert({curmax[*col.begin()], *col.begin()});

    int lim = v.size()+1;

    curmax[lim] = checkRight(*col.rbegin());
    dis.insert({curmax[lim], lim});
    col.insert(lim);

    int pre = 0;
    for(auto i : col){
        if(pre && i != lim){
            curmax[i] = solveTwo(pre,i);
            dis.insert({curmax[i], i});
        }
        pre = i;
    }

    cout << dis.rbegin()->first << '\n';

    for(int i = 1; i <= q; i++){
        if(!check[qr[i].first][qr[i].second]){
            int c = qr[i].second;
            updateCol(c, qr[i].first);

            if(col.find(c) != col.end()) dis.erase({curmax[c], c});

            col.insert(c);
            auto it = col.lower_bound(c);
            if(it == col.begin()){
                curmax[c] = checkLeft(c);
                dis.insert({curmax[c],c});
            }else{
                auto p = it;
                p--;
                curmax[c] = solveTwo(*p,c);
                dis.insert({curmax[c],c});
            }

            it++;
            if(*it != lim){
                dis.erase({curmax[*it], *it});
                curmax[*it] = solveTwo(c,*it);
                dis.insert({curmax[*it],*it});
            }else{
                dis.erase({curmax[*it], *it});
                curmax[*it] = checkRight(c);
                dis.insert({curmax[*it],*it});
            }

            it--;

            auto be = it;
            while(be != col.begin()){
                be--;
                dis.erase({curmax[*be], *be});

                if(be == col.begin()){
                    curmax[*be] = checkLeft(*be);
                    dis.insert({curmax[*be],*be});
                }else{
                    auto p = be;
                    p--;
                    curmax[*be] = solveTwo(*p,*be);
                    dis.insert({curmax[*be],*be});
                }
                if(*be < le[c]) break;
            }

            auto af = it;
            while(af != col.end()){
                af++;
                if(*af == lim) break;
                //if(*af > ri[c]) break;
                dis.erase({curmax[*af], *af});
                auto p = af;
                p--;
                curmax[*af] = solveTwo(*p,*af);
                dis.insert({curmax[*af],*af});
                if(*af > ri[c]) break;
            }

            it = col.lower_bound(lim);
            dis.erase({curmax[*it], *it});
            auto p = it;
            p--;
            curmax[*it] = checkRight(*p);
            dis.insert({curmax[*it],*it});

            check[qr[i].first][qr[i].second] = 1;
            cnt[qr[i].second]++;
        }else{
            int c = qr[i].second;
            removeCol(c, qr[i].first);
            cnt[c]--;

            dis.erase({curmax[c], c});
            auto it = col.lower_bound(c);
            auto af = it; auto be = it;

            if(!cnt[c]){
                curmax[c] = 0;
                while(af != col.end()){
                    af++;
                    if(*af == lim) break;
                    dis.erase({curmax[*af], *af});
                    auto p = af;
                    p--;
                    if(*p == c){
                        if(p == col.begin()) curmax[*af] = checkLeft(*af);
                        else{
                            p--;
                            curmax[*af] = solveTwo(*p,*af);
                        }
                    }else curmax[*af] = solveTwo(*p,*af);
                    dis.insert({curmax[*af],*af});
                    if(*af > ri[c]) break;
                }

                while(be != col.begin()){
                    be--;
                    dis.erase({curmax[*be], *be});

                    if(be == col.begin()){
                        curmax[*be] = checkLeft(*be);
                        dis.insert({curmax[*be],*be});
                    }else{
                        auto p = be;
                        p--;
                        curmax[*be] = solveTwo(*p,*be);
                        dis.insert({curmax[*be],*be});
                    }
                    if(*be < le[c]) break;
                }
                col.erase(c);
            }else{
                auto be = it;
                while(be != col.begin()){
                    be--;
                    dis.erase({curmax[*be], *be});

                    if(be == col.begin()){
                        curmax[*be] = checkLeft(*be);
                        dis.insert({curmax[*be],*be});
                    }else{
                        auto p = be;
                        p--;
                        curmax[*be] = solveTwo(*p,*be);
                        dis.insert({curmax[*be],*be});
                    }
                    if(*be < le[c]) break;
                }

                auto af = it;
                while(af != col.end()){
                    af++;
                    if(*af == lim) break;
                    dis.erase({curmax[*af], *af});
                    auto p = af;
                    p--;
                    curmax[*af] = solveTwo(*p,*af);
                    dis.insert({curmax[*af],*af});
                    if(*af > ri[c]) break;
                }

                if(it != col.begin()){
                    auto be = it;
                    be--;
                    curmax[c] = solveTwo(*be,c);
                    dis.insert({curmax[c],c});
                }else{
                    curmax[c] = checkLeft(c);
                    dis.insert({curmax[c],c});
                }

                it++;
                if(*it != lim){
                    dis.erase({curmax[*it], *it});
                    curmax[*it] = solveTwo(c,*it);
                    dis.insert({curmax[*it],*it});
                }else{
                    dis.erase({curmax[*it], *it});
                    curmax[*it] = checkRight(c);
                    dis.insert({curmax[*it],*it});
                }

                it--;
            }

            it = col.lower_bound(lim);
            dis.erase({curmax[*it], *it});
            auto p = it;
            p--;
            curmax[*it] = checkRight(*p);
            dis.insert({curmax[*it],*it});

            check[qr[i].first][qr[i].second] = 0;
        }

//        for(auto p : dis){
//            cout << p.first << ' ' << p.second << '\n';
//        }
        cout << dis.rbegin()->first << '\n';
    }
    return 0;
}
