#include <bits/stdc++.h>

using namespace std;

struct TrieNode{
    TrieNode* child[26];
    long long val;
    TrieNode(){
        for(int i = 0; i < 26; i++) child[i] = NULL;
        val = 0;
    }
};

string a[300005];
long long w[300005];

void add(TrieNode* root, string s){
    TrieNode* cur = root;
    for(auto c : s){
        if(cur->child[c-'A'] == NULL){
            cur->child[c-'A'] = new TrieNode();
        }
        cur = cur->child[c-'A'];
    }
}

void dfs(TrieNode* root, string s, long long &res, int &i){
    TrieNode* cur = root;

    int cnt = 0;
    for(auto c : s){
        if(cur->child[c-'A'] == NULL) return;
        cur = cur->child[c-'A'];
        cnt++;
        if(cnt != s.size()) res = max(res, cur->val + w[i]);
    }
    cur->val = max(cur->val, res);
}

vector<int> pp[100005];
long long maxval[100005];

vector<int> hv;
int id[100005];
long long maxpre[355];
bool check[100005][355];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i] >> w[i];
    TrieNode* root = new TrieNode();
    for(int i = 1; i <= n; i++) add(root, a[i]);

    for(int i = 1; i <= m; i++){
        int x,y;
        cin >> x >> y;
        pp[x].push_back(y);
        pp[y].push_back(x);
    }

    int lim = sqrt(1e5);
    for(int i = 1; i <= 1e5; i++) if(pp[i].size() > lim){
        hv.push_back(i);
        id[i] = hv.size();
    }

    for(int i = 1; i <= 1e5; i++){
        for(auto j : pp[i]) if(id[j]) check[i][id[j]] = true;
    }

    long long ans = 0;
    for(int i = n; i >= 1; i--){
        long long res = w[i];
        if(pp[w[i]].size() <= lim){
            for(auto j : pp[w[i]]) res = max(res, maxval[j]+w[i]);
        }else{
            res = max(res, maxpre[id[w[i]]] + w[i]);
        }

        dfs(root,a[i],res,i);
        maxval[w[i]] = max(maxval[w[i]], res);
        for(int j = 1; j <= hv.size(); j++) if (check[w[i]][j]) maxpre[j] = max(maxpre[j], res);

        ans = max(ans,res);
    }

    cout << ans;
    return 0;
}
