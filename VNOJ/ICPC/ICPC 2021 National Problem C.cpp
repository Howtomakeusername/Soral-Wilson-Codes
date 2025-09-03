#include<bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

pair<int,int> p[105];
int d1[105];
int d2[105][105];
int d3[105][105][105];
int sum[105][105][105];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    vector<pair<tuple<double,double,double>, tuple<int,int,int>>> v;
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i].first >> p[i].second;

    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j && p[i] != p[j]){
        for(int k = 1; k <= n; k++) if(k != i && k != j && p[i] != p[k] && p[j] != p[k]){
            if( ((p[i].second - p[j].second) * (p[i].first - p[k].first)) == ((p[i].second - p[k].second) * (p[i].first - p[j].first)) ) continue;

            vector<double> vec;

            int x = abs(p[i].first - p[j].first), y = abs(p[i].second - p[j].second);
            double dis = sqrtl(x*x + y*y);
            vec.push_back(dis);

            x = abs(p[j].first - p[k].first), y = abs(p[j].second - p[k].second);
            dis = sqrtl(x*x + y*y);
            vec.push_back(dis);

            x = abs(p[i].first - p[k].first), y = abs(p[i].second - p[k].second);
            dis = sqrtl(x*x + y*y);
            vec.push_back(dis);

            v.push_back({make_tuple(vec[0], vec[1], vec[2]), make_tuple(i,j,k)});
        }
    }

    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        vector<tuple<int,int,int>> cur;
        tuple<double,double,double> edge = v[i].first;
        cur.push_back(v[i].second);
        while(i < v.size()-1 && v[i+1].first == edge){
            i++;
            cur.push_back(v[i].second);
        }

        int d0 = cur.size();
        for(auto p : cur){
            d1[get<0>(p)]++;
            d1[get<1>(p)]++;
            d1[get<2>(p)]++;

            vector<int> vec;
            vec.push_back(get<0>(p));
            vec.push_back(get<1>(p));
            vec.push_back(get<2>(p));
            sort(vec.begin(), vec.end());


            d2[vec[0]][vec[1]]++;
            d2[vec[1]][vec[2]]++;
            d2[vec[0]][vec[2]]++;

            d3[vec[0]][vec[1]][vec[2]]++;
        }

        for(auto p : cur){
            vector<int> vec;
            vec.push_back(get<0>(p));
            vec.push_back(get<1>(p));
            vec.push_back(get<2>(p));
            sort(vec.begin(), vec.end());

            sum[get<0>(p)][get<1>(p)][get<2>(p)] += d0 - d1[get<0>(p)] - d1[get<1>(p)] - d1[get<2>(p)];
            //cout << sum[get<0>(p)][get<1>(p)][get<2>(p)] << endl;
            sum[get<0>(p)][get<1>(p)][get<2>(p)] += d2[vec[0]][vec[1]] + d2[vec[1]][vec[2]] + d2[vec[0]][vec[2]];
            //cout << sum[get<0>(p)][get<1>(p)][get<2>(p)] << endl;
            sum[get<0>(p)][get<1>(p)][get<2>(p)] -= d3[vec[0]][vec[1]][vec[2]];
            //cout << sum[get<0>(p)][get<1>(p)][get<2>(p)] << endl;
            //cout << get<0>(p) << ' ' << get<1>(p) << ' ' << get<2>(p) << ' ' << cur.size() << endl;
        }

        for(auto p : cur){
            d1[get<0>(p)]--;
            d1[get<1>(p)]--;
            d1[get<2>(p)]--;

            vector<int> vec;
            vec.push_back(get<0>(p));
            vec.push_back(get<1>(p));
            vec.push_back(get<2>(p));
            sort(vec.begin(), vec.end());


            d2[vec[0]][vec[1]]--;
            d2[vec[1]][vec[2]]--;
            d2[vec[0]][vec[2]]--;

            d3[vec[0]][vec[1]][vec[2]]--;
        }


//        cout << get<0>(edge) << ' ' << get<1>(edge) << ' ' << get<2>(edge) << endl;
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) for(int j = i+1; j <= n; j++) for(int k = j+1; k <= n; k++) ans += sum[i][j][k];
    cout << ans;

    return 0;
}
