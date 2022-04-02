#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
const long long LINF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adjs(n);
    rep(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        adjs[a].emplace_back(b, c);
        adjs[b].emplace_back(a, c);
    }

    auto dijkstra = [&](int s) -> vector<long long> {
        vector<long long> dist(n, LINF);
        dist[s] = 0;

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
        q.push(pair<long long, int>(0, s));

        while(!q.empty()) {
            auto [dist_v, v] = q.top();
            q.pop();

            if(dist[v] != dist_v) continue;

            for(auto [u, cost] : adjs[v]) {
                long long dist_u = dist_v + cost;
                if(dist[u] > dist_u) {
                    dist[u] = dist_u;
                    q.push(pair<long long, int>(dist_u, u));
                }
            }
        }

        return dist;
    };
    
    // 頂点Kを経由する 1 -> K -> N は
    // 1 -> K と N -> K の合計で求まる
    vector<long long> dist_1 = dijkstra(0);
    vector<long long> dist_n = dijkstra(n - 1);

    rep(k, n) cout << dist_1[k] + dist_n[k] << '\n';

    return 0;
}

