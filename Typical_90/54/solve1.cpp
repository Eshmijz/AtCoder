#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)

int n, m;
vector<vector<int>> g;
vector<int> dist;

int main() {
    int n, m;
    cin >> n >> m;

    // 人と論文を頂点としたグラフ
    g.resize(n + m);
    rep(i, m) {
        int k;
        cin >> k;
        rep(j, k) {
            int r;
            cin >> r;
            --r;
            // 論文と人に辺を張る
            g[r].push_back(n + i);
            g[n + i].push_back(r);
        }
    }

    // 初期値 -2 で更新 (出力するときに楽)
    dist.resize(n + m, -2);
    dist[0] = 0;

    deque<int> q;
    q.push_back(0);

    while(!q.empty()) {
        int v = q.front();
        q.pop_front();

        for(int u : g[v]) {
            // 頂点を訪れたことがあるか
            if(dist[u] != -2) continue;
            dist[u] = dist[v] + 1;
            q.push_back(u);
        }
    }

    // 論文を跨ぐため、人 -> 人の距離が2になっているため2で割る
    rep(i, n) cout << dist[i] / 2 << '\n';

    return 0;
}
