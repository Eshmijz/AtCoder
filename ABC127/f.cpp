#include <iostream>
#include <queue>
using namespace std;
using ll = long long;
#define rep(i, n) for(int i = 0; i < n; ++i)

int main() {
    int q;
    cin >> q;

    priority_queue<ll> L;
    priority_queue<ll, vector<ll>, greater<ll>> R;
    ll sumb = 0, mn = 0;

    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int a, b;
            cin >> a >> b;
            sumb += b;

            L.emplace(a), R.emplace(a);

            while(L.top() > R.top()) {
                ll l = L.top(), r = R.top();
                mn += abs(l - r);
                R.emplace(l), L.pop();
                L.emplace(r), R.pop();
            }
        } else
            cout << L.top() << " " << mn + sumb << endl;
    }

    return 0;
}
