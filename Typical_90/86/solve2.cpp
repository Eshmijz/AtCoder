#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)

constexpr int mod = 1000000007;
// 問題変数
int n, q;
int x[51], y[51], z[51];
long long _w[51];

// 入力された w (十進数) を二進数にする
string w[51];
long long ans;

// x, y, z の位置のすべてが0であるかを判定する
bool all_0(string B, int i) {
    return B[x[i]] == '0' && B[y[i]] == '0' && B[z[i]] == '0';
}

// x, y, z の位置のどれかが1であるかを判定する
bool any_1(string B, int i) {
    return B[x[i]] == '1' || B[y[i]] == '1' || B[z[i]] == '1';
}

int main() {
    cin >> n >> q;
    rep(i, q) {
        cin >> x[i] >> y[i] >> z[i] >> _w[i];
        --x[i], --y[i], --z[i];
    }
    rep(i, q) {
        w[i] = bitset<60>(_w[i]).to_string();
        reverse(w[i].begin(), w[i].end());
    }

    ans = 1;
    // 各桁、独立に条件を満たす個数を求める
    rep(d, 60) {
        int cnt = 0;
        rep(_S, 1 << n) {
            // 二進数変換
            string S = bitset<60>(_S).to_string();
            reverse(S.begin(), S.end());

            bool ok = true;
            rep(i, q) {
                if(w[i][d] == '0') ok &= all_0(S, i);
                if(w[i][d] == '1') ok &= any_1(S, i);
            }
            if(ok) cnt++;
        }
        ans *= cnt;
        ans %= mod;
    }
    cout << ans << '\n';
}
