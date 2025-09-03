#include<bits/stdc++.h>

using namespace std;

#define int unsigned long long

const uint64_t inf = 10000000000000000000ULL;

inline uint64_t mod_mult64(uint64_t a, uint64_t b, uint64_t m) {
    return __int128_t(a) * b % m;
}
uint64_t mod_pow64(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t ret = (m > 1);
    for (;;) {
        if (b & 1) ret = mod_mult64(ret, a, m);
        if (!(b >>= 1)) return ret;
        a = mod_mult64(a, a, m);
    }
}

// Works for all primes p < 2^64
bool is_prime(uint64_t n) {
    if (n <= 3) return (n >= 2);
    static const uint64_t small[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
        149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
    };
    for (size_t i = 0; i < sizeof(small) / sizeof(uint64_t); ++i) {
        if (n % small[i] == 0) return n == small[i];
    }

    // Makes use of the known bounds for Miller-Rabin pseudoprimes.
    static const uint64_t millerrabin[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    };
    static const uint64_t A014233[] = {  // From OEIS.
        2047LL, 1373653LL, 25326001LL, 3215031751LL, 2152302898747LL,
        3474749660383LL, 341550071728321LL, 341550071728321LL,
        3825123056546413051LL, 3825123056546413051LL, 3825123056546413051LL, 0,
    };
    uint64_t s = n-1, r = 0;
    while (s % 2 == 0) {
        s /= 2;
        r++;
    }
    for (size_t i = 0, j; i < sizeof(millerrabin) / sizeof(uint64_t); i++) {
        uint64_t md = mod_pow64(millerrabin[i], s, n);
        if (md != 1) {
            for (j = 1; j < r; j++) {
                if (md == n-1) break;
                md = mod_mult64(md, md, n);
            }
            if (md != n-1) return false;
        }
        if (n < A014233[i]) return true;
    }
    return true;
}

int prime[3000005];
vector<int> p;

void Sieve(int lim){
    for(int i = 2; i <= lim; i++) prime[i] = 1;
    for(int i = 2; i*i <= lim; i++){
        if(prime[i]){
            for(int j = i*i; j <= lim; j += i){
                prime[j] = 0;
            }
        }
    }
    for(int i = 2; i <= lim; i++) if(prime[i]) p.push_back(i);
}

set<int> mp;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("BANYAN.inp", "r", stdin);
//    freopen("BANYAN.out", "w", stdout);
    Sieve(3e6);
    for(int i = 0; i < p.size(); i++){
        int mul = 1;
        for(int j = i; j < p.size(); j++){
            if(mul > inf/p[j]) break;
            mul *= p[j];
            mp.insert(mul);
        }
    }

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(mp.find(n) != mp.end()){
            cout << "NICE" << '\n';
            continue;
        }

        if(is_prime(n)){
            cout << "NICE" << '\n';
            continue;
        }

        int border = sqrtl(n)+3;
        while(border*border > n) border--;

        int x = border+1;
        if(x%2 == 0) x++;
        while(!is_prime(x)) x += 2;

        if(n%x){
            cout << "UGLY" << '\n';
            continue;
        }

        int y = x-1;
        if(y%2 == 0) y--;

        while(!is_prime(y) && y >= 2 && x-y <= 10000) y -= 2;

        if(n/x == y) cout << "NICE" << '\n';
        else cout << "UGLY" << '\n';
    }

    return 0;
}
