#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)

// vectorを出力する用
template <class T> ostream &operator<<(ostream &os, vector<T> P) {
    for(int i = 0; i < P.size(); ++i) {
        if(i > 0) { os << " "; }
        os << P[i];
    }
    return os;
}

// 問題変数
int n, q, x, y;
vector<int> a;

// 和としてあり得るのは　0〜8888 なので
constexpr int m = 8890;

// 制約を満たすかをチェックする用
vector<vector<int>> P;
vector<int> C;
// 選んだ数の集合
vector<int> S;
// 和がxになる集合を入れる
vector<vector<vector<int>>> ans(m);

// 2パターンみつかったら、終了
void finish(int x) {
    cout << ans[x][0].size() << '\n';
    cout << ans[x][0] << '\n';
    cout << ans[x][1].size() << '\n';
    cout << ans[x][1] << '\n';
    exit(0);
}

/**
 * @fn
 * 小さい方から選ぶか選ばないかを決めていく
 * @param (int i) N個の要素のうち、先頭から何番目か
 * @param (int tot) 選んだ集合の和
 * @return
 */
void dfs(int i, int tot) {
    if(i == n) {
        ans[tot].push_back(S);
        if(ans[tot].size() == 2) finish(tot);
        return;
    }
    // 選ばない
    dfs(i + 1, tot);

    // 選ぶ (選んだ集合の中にi番目とペアのカードがないかをチェック)
    if(C[i] == 0) {
        // i番目とペアで選んではいけない数をチェックする
        for(int j : P[i]) C[j]++;
        // 選んだ数の集合に i 番目を追加
        S.push_back(i + 1);
        dfs(i + 1, tot + a[i]);
        // 探索が終了したので制約を解除する
        for(int j : P[i]) C[j]--;
        // 選んだ数の集合から i 番目を削除
        S.pop_back();
    }
}

int main() {
    cin >> n >> q;
    a.resize(n);
    rep(i, n) cin >> a[i];
    C.resize(n);
    P.resize(n);
    rep(i, q) {
        cin >> x >> y;
        --x, --y;
        P[x].push_back(y);
    }

    dfs(0, 0);

    return 0;
}
