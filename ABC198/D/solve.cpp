#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)

int main() {
    vector<string> s(3);
    rep(i, 3) cin >> s[i];
    map<char, long long> ps;
    rep(i, 3) {
        long long x = pow(10, (int)s[i].size());
        if(i == 2) x = -x;
        rep(j, (int)s[i].size()) {
            x /= 10;
            ps[s[i][j]] += x;
        }
    }

    bool isAnswered = false;

    // 文字の種類が10を超える場合、構築不可能
    if(ps.size() > 10) {
        cout << "UNSOLVABLE" << '\n';
        isAnswered = true;
    }

    vector<int> p(10);
    iota(p.begin(), p.end(), 0);

    do {
        long long tot = 0;
        int x = 0;
        // 文字と数値を対応させる
        map<char, int> dict;
        for(auto [key, val] : ps) {
            tot += p[x] * val;
            dict[key] = p[x++];
        }
        // 多項式を満たさない
        if(tot != 0) continue;
        // 先頭の文字に0が割り当てられているか
        bool leadingZero = false;
        rep(i, 3) if(dict[s[i][0]] == 0) leadingZero = true;
        if(leadingZero) continue;

        // ここまで来れば条件を満たしているので、文字を数値に変換する
        rep(i, 3) {
            long long ans = 0;
            rep(j, (int)s[i].size()) ans = ans * 10 + dict[s[i][j]];
            cout << ans << '\n';
        }
        isAnswered = true;
    } while(next_permutation(p.begin(), p.end()) && !isAnswered);

    if(!isAnswered) cout << "UNSOLVABLE" << '\n';

    return 0;
}
