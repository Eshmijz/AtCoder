#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)

// 桁が大きいので文字列として受け取る
string N;
int K;
// サイズを大きめに確保
int dp[110][10][2];

int main() {
    cin >> N >> K;
    // 0桁、0以外の数が0個、一致しているのが1通り
    dp[0][0][0] = 1;
    // 数字の長さ
    int n = N.size();

    rep(i, n) rep(j, K + 1) rep(k, 2) rep(x, 10) {
        // i桁目の数字を取得
        int num = N[i] - '0';
        int ni = i + 1;
        int nj = j + (x != 0); // 0以外ならば、0以外の個数が1増える
        int nk = k | (x < num); // i桁目の数字未満ならば、未満への遷移
        // 一致している状態からi桁目の数字以上には遷移できない（N以上になる）
        if(x > num && k == 0) continue;
        // 0以外の個数がK個を超える通り数は答えに寄与しない
        if(nj > K) continue;
        dp[ni][nj][nk] += dp[i][j][k];
    }
    // n桁目まで見た時の0以外の個数がK個の通り数が答え
    cout << dp[n][K][0] + dp[n][K][1] << '\n';
    return 0;
}
