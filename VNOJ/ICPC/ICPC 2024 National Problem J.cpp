#include<bits/stdc++.h>

using namespace std;

int ptl[600005];
int ptr[600005];
char a[600005];

int type = 0;
int slot = 0;
int save = 0;
int n;

void solveOne(){
    int l = save;
    //cout << l << endl;
    while( (type == 0 && (a[l] != 'g' || a[ptr[l]] != 'r')) || (type == 1 && (a[l] != 'r' || a[ptr[l]] != 'g')) ) l = ptr[l];

    while(slot){
        cout << l << ' ';
        slot -= 3;
        l = ptr[l];
        l = ptr[l];
        l = ptr[l];
        type ^= 1;
        while( (type == 0 && (a[l] != 'g' || a[ptr[l]] != 'r')) || (type == 1 && (a[l] != 'r' || a[ptr[l]] != 'g')) ) l = ptr[l];
    }
}

//0 = ggrg, 1 = grgg, 2 = rrgr, 3 = rgrr
set<int> pos[5];
set<int> contri[600005];

void nextFour(int i){
    string x = "";
    int c = i;
    x += a[c]; c = ptr[c];
    x += a[c]; c = ptr[c];
    x += a[c]; c = ptr[c];
    x += a[c];
    //cout << x << ' ' << i << ' ' << ptr[i] << ' ' << ptl[i] << endl;

    if(x == "ggrg"){
        pos[0].insert(i);
        contri[i].insert(0);
    }
    if(x == "grgg"){
        pos[1].insert(i);
        contri[i].insert(1);
    }
    if(x == "rrgr"){
        pos[2].insert(i);
        contri[i].insert(2);
    }
    if(x == "rgrr"){
        pos[3].insert(i);
        contri[i].insert(3);
    }
}

void removeFromRight(int org, int i){
    int c = i;
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();

    c = ptr[c];
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();

    c = ptr[c];
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();

    c = ptr[c];
    ptr[org] = c;
    ptl[c] = org;
}

void reCalLeft(int i){
    int c = i;
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();
    nextFour(c);

    c = ptl[c];
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();
    nextFour(c);

    c = ptl[c];
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();
    nextFour(c);
}

void reCalRight(int i){
    int c = i;
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();
    nextFour(c);

    c = ptr[c];
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();
    nextFour(c);

    c = ptr[c];
    for(auto x : contri[c]) pos[x].erase(c);
    contri[c].clear();
    nextFour(c);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        n *= 6;
        string tmp;
        cin >> tmp;

        for(int i = 1; i <= n; i++) a[i] = tmp[i-1];
        slot = n;
        save = 1;

        char pre = '0';
        int cur = 0;
        for(int i = 1; i <= n; i++){
            ptl[i] = i-1;
            ptr[i] = i+1;
            if(a[i] == pre) cur++;
            pre = a[i];
        }
        ptl[1] = n;
        ptr[n] = 1;

        if(a[n] != a[1]){
            if(cur == 0) cur++;
        }else{
            cur++;
        }

        if(cur > n/3){
            cout << "NO" << '\n';
            for(int i = 1; i <= n; i++) ptl[i] = 0, ptr[i] = 0;
            continue;
        }

        if(cur == 1){
            cout << "YES" << '\n';
            solveOne();
            cout << '\n';
            for(int i = 1; i <= n; i++) ptl[i] = 0, ptr[i] = 0;
            continue;
        }

        vector<int> ans;
        for(int i = 1; i <= n; i++) nextFour(i);

        while( (pos[0].size() || pos[1].size() || pos[2].size() || pos[3].size()) && slot > 3){
            int org = 0;
            if(type == 0){
                if(pos[0].size()){
                    int p = *pos[0].begin();
                    ans.push_back(ptr[p]);
                    org = p;

                    removeFromRight(org, ptr[p]);
                }else if(pos[1].size()){
                    int p = *pos[1].begin();
                    ans.push_back(p);
                    org = ptl[p];

                    removeFromRight(org, p);
                }
            }else{
                if(pos[2].size()){
                    int p = *pos[2].begin();
                    ans.push_back(ptr[p]);
                    org = p;

                    removeFromRight(org, ptr[p]);
                }else if(pos[3].size()){
                    int p = *pos[3].begin();
                    ans.push_back(p);
                    org = ptl[p];

                    removeFromRight(org, p);
                }
            }

            save = org;
            slot -= 3;
            if(slot > 3){
                reCalLeft(org);
                reCalRight(ptr[org]);
            }
            type ^= 1;
        }

        cout << "YES" << '\n';
        for(auto i : ans) cout << i << ' ';
        solveOne();
        cout << '\n';
        for(int i = 1; i <= n; i++){
            ptl[i] = 0, ptr[i] = 0;
            contri[i].clear();
        }
        for(int k = 0; k <= 3; k++) pos[k].clear();
    }
    return 0;
}
