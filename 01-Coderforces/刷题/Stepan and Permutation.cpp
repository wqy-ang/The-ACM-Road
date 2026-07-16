// 2026-07-16
// C. Stepan and Permutation
// https://codeforces.com/contest/2244/problem/C
#include <bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define QwQ cin.tie(0)->sync_with_stdio(0);
using namespace std;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n);
    vector<PII> pa(n);
    for(int i=0; i<n; i++) {
        cin >> a[i];
        pa[i] = {a[i], i};
    }

    if(is_sorted(a.begin(), a.end())) {
        cout << "YES\n";
        return;
    }

    vector<int> fa(n, -1);

    function<int(int)> find;
    find = [&](int x) -> int {
        if(fa[x] < 0) return x;
        return fa[x] = find(fa[x]);
    };

    function<void(int, int)> merge;
    merge = [&](int x, int y) -> void {
        // 先判断越界
        if(x >= n || y >= n) return;
        // 再调用find
        int rx = find(x);
        int ry = find(y);
        if(rx == ry) return;
        if(abs(fa[rx]) < abs(fa[ry])) swap(rx, ry);
        fa[rx] += fa[ry];
        fa[ry] = rx;
    };

    for(int i=0; i<n; i++) {
        int dx = i+x, dy = i+y;
        if(dx >= n && dy >= n) break;
        merge(i, dx);
        merge(i, dy);
    }

    sort(pa.begin(), pa.end());
    for(int i=0; i<n; i++) {
        if(find(i) != find(pa[i].second)) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

signed main() {
    QwQ
    int t = 1; cin >> t;
    while(t--) solve();
    return 0;
}