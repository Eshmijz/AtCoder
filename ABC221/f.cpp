#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for(int i = 0; i < n; ++i)
using mint = modint998244353;

struct D {
    // 距離の最大値、その頂点、条件を満たす頂点の数
    int mx, v, cnt;
    D() : mx(0), v(0), cnt(0){};

    void update(const D &x) {
        if(mx < x.mx) mx = x.mx, v = x.v;
        cnt += x.cnt;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 頂点間に頂点を追加
    // 直径の偶奇を揃えるため
    vector<vector<int>> g(2 * n);
    rep(i, n) if(i != 0) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(n + i);
        g[n + i].push_back(u);
        g[v].push_back(n + i);
        g[n + i].push_back(v);
    }

    // 木の中心
    int mid;
    vector<int> dist(2 * n);
    auto dfs = [&](auto &f, int v, int pre = -1, int dep = 0, int tg = -1) -> D {
        D d;
        if(dep == tg && dist[v] == tg) mid = v;
        if(dep == tg) d.cnt++;
        d.mx = dep, d.v = v;
        dist[v] = dep;
        for(int u : g[v]) {
            if(u == pre) continue;
            d.update(f(f, u, v, dep + 1, tg));
        }
        return d;
    };

    // 頂点1（0は使用しない）から
    D d1 = dfs(dfs, 1);
    // 直径を求める
    D ds = dfs(dfs, d1.v);
    // 木の中心となる距離
    int d2 = ds.mx / 2;
    // middleを探し
    dfs(dfs, ds.v, -1, 0, d2);

    // s1 は1個選ぶ組み合わせ
    mint ans = 1, s1 = 0;
    for(int u : g[mid]) {
        D d = dfs(dfs, u, mid, 0, d2 - 1);
        ans *= d.cnt + 1;
        s1 += d.cnt;
    }
    // 1個選ぶ組み合わせと0個選ぶ組み合わせを引く
    ans -= s1 + 1;

    cout << ans.val() << '\n';
    return 0;
}
