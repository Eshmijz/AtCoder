#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for(int i = 0; i < n; ++i)
using mint = modint1000000007;
using ll = long long;
 
struct combination {
    vector<mint> fact, ifact;
    combination(int n) : fact(n + 1), ifact(n + 1) {
        fact[0] = 1;
        for(int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
        ifact[n] = fact[n].inv();
        for(int i = n; i >= 1; --i) ifact[i - 1] = ifact[i] * i;
    }
    mint operator()(int n, int k) {
        if(k < 0 || k > n) return 0;
        return fact[n] * ifact[k] * ifact[n - k];
    }
} comb(2000005);
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    ll n, m, k;
    cin >> n >> m >> k;
 
    mint ans = 0;
    rep(i, n) { ans += (ll)(i * (n - i) * m * m); }
    rep(i, m) { ans += (ll)(i * (m - i) * n * n); }
 
    ans *= comb(n * m - 2, k - 2);
    cout << ans.val() << endl;
 
    return 0;
}
