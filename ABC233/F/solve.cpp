#include <bits/stdc++.h>
using namespace std;
// Union-find を使用する
#include <atcoder/all>
using namespace atcoder;

#define rep(i, n) for(int i = 0; i < n; ++i)

template <class T> ostream &operator<<(ostream &os, vector<T> P) {
    for(int i = 0; i < P.size(); ++i) {
        if(i > 0) { os << " "; }
        os << P[i];
    }
    return os;
}

void solve();
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}

// 連結成分内に見つからなければ、構築不可能
void No() {
    cout << -1 << '\n';
    exit(0);
}
 
void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    rep(i, n) cin >> p[i], --p[i];
 
    dsu t(n);
    // グラフ
    vector<vector<int>> g(n);
    // 操作する番号
    map<P, int> edge;
  
    int m;
    cin >> m;
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        if(t.same(a, b)) continue;
        t.merge(a, b);
        // 入力で a < b が保証されている
        edge[make_pair(a, b)] = i + 1;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    // 操作手順を格納していく
    vector<int> ans;
 
    auto dfs2 = [&](auto f, int tg, int v, int pre = -1) -> bool {
        if(p[v] == tg) return true;
        for(int u : g[v]) {
            if(u == pre) continue;
            // 探索して見つかったら
            if(f(f, tg, u, v)) {
                if(u < v) swap(u, v);
                ans.push_back(edge[make_pair(v, u)]);
                swap(p[v], p[u]);
                return true;
            }
        }
        return false;
    };
 
    auto dfs1 = [&](auto f, int v, int pre = -1) -> void {
        for(int u : g[v])
            // 先に部分木を全て一致させる
            if(u != pre) f(f, u, v);
        // 連結成分内に見つからなければ、即終了
        if(!dfs2(dfs2, v, v)) No();
    };
 
    rep(i, n) {
        // 連結成分内で1回dfsをすれば良いので、連結成分のリーダーであればdfs
        if(t.leader(i) == i) dfs1(dfs1, i);
    }
    cout << ans.size() << '\n';
    cout << ans << '\n';
}
