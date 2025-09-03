#include <bits/stdc++.h>

using namespace std;

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
};

int ccw(Point a, Point b, Point c) {
	long long val = 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (c.x - a.x) * (b.y - a.y);
	return val < 0 ? -1 : !!val;
}

bool onSegment(Point p, Point q, Point r) {
	return min(p.x, r.x) <= q.x && q.x <= max(p.x, r.x) &&
		   min(p.y, r.y) <= q.y && q.y <= max(p.y, r.x);
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
	int o1 = ccw(p1, q1, p2);
	int o2 = ccw(p1, q1, q2);
	int o3 = ccw(p2, q2, p1);
	int o4 = ccw(p2, q2, q1);
	if (o1 != o2 && o3 != o4) return true;
	if (!o1 && onSegment(p1, p2, q1)) return true;
	if (!o2 && onSegment(p1, q2, q1)) return true;
	if (!o3 && onSegment(p2, p1, q2)) return true;
	if (!o4 && onSegment(p2, q1, q2)) return true;
	return false;
}

Point p[5][200005];
pair<int,int> e[5][700005];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("mbp.inp","r",stdin);
//    freopen("mbp.out","w",stdout);
    int t;
    cin >> t;
    while(t--){
        int na,ma,nb,mb;
        cin >> na >> ma;
        for(int i = 1; i <= na; i++) cin >> p[1][i].x >> p[1][i].y;
        for(int i = 1; i <= ma; i++) cin >> e[1][i].first >> e[1][i].second;
        cin >> nb >> mb;
        for(int i = 1; i <= nb; i++) cin >> p[2][i].x >> p[2][i].y;
        for(int i = 1; i <= mb; i++) cin >> e[2][i].first >> e[2][i].second;

        pair<int,int> ans;
        for(int i = 1; i <= na; i++){
            if(ans.first) break;
            for(int j = 1; j <= nb; j++){
                int flag = 1;
                for(int k = 1; k <= ma; k++) if(e[1][k].first != i && e[1][k].second != i){
                    if(doIntersect(p[1][i], p[2][j], p[1][e[1][k].first], p[1][e[1][k].second])){
                        flag = 0;
                        break;
                    }
                }
                if(!flag) continue;
                for(int k = 1; k <= mb; k++) if(e[2][k].first != j && e[2][k].second != j){
                    if(doIntersect(p[1][i], p[2][j], p[2][e[2][k].first], p[2][e[2][k].second])){
                        flag = 0;
                        break;
                    }
                }
                if(!flag) continue;

                ans = {i,j};
                break;
            }
        }
        if(ans.first) cout << ans.first << ' ' << ans.second << '\n';
        else cout << 0 << '\n';
    }
    return 0;
}
