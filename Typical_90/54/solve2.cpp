#include <bits/stdc++.h>
using namespace std;

// 問題変数
int n, m, k, r;

// グラフ
vector<vector<int>> g;
// 各頂点への最短距離
vector<int> dist;

int main() {
    cin >> n >> m;

    // 人と論文を頂点としたグラフ
    g.resize(n + m);
    for(int i = 0; i < m; ++i) {
        cin >> k;
        for(int j = 0; j < k; ++j) {
            cin >> r;
            --r;
            // 論文と人に辺を張る
            g[r].push_back(n + i);
            g[n + i].push_back(r);
        }
    }

    // 初期値 -1 で更新
    dist.resize(n + m, -1);
    dist[0] = 0;

    deque<int> q;
    q.push_back(0);

    while(!q.empty()) {
        int v = q.front();
        q.pop_front();

        for(int u : g[v]) {
            // 頂点を訪れたことがあるか
            if(dist[u] != -1) continue;
            // 人 -> 論文には 1 の重みをつける
            if(v < n) // 0 ~ n-1 は 人
                dist[u] = dist[v] + 1;
            else // n ~ n+m は 論文
                dist[u] = dist[v];
            q.push_back(u);
        }
    }

    // 論文頂点を削除
    dist.resize(n);
    // 出力
    for(int ans : dist) cout << ans << '\n';

    return 0;
}
