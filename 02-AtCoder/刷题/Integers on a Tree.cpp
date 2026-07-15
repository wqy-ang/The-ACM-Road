// 2026-07-15
// https://atcoder.jp/contests/arc063/tasks/arc063_c
#include <bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define QwQ cin.tie(0)->sync_with_stdio(0);
using namespace std;

const int N = 1E5 + 5;

vector<int> e[N], a(N);
vector<bool> vis(N), num(N);

signed main() {
    QwQ
    // Build Tree
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    // 优先队列，权值小的在队头
    priority_queue<PII, vector<PII>, greater<PII>> pq;

    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int v, p;
        cin >> v >> p;
        a[v] = p;
        num[v] = true; // 标记已填数字
        pq.push({p, v});
    }

    while (!pq.empty()) {
        auto [p, u] = pq.top();
        pq.pop();
        vis[u] = true; // 标记已访问

        for (int &v : e[u]) {
            if (!vis[v] && num[v]) {
                if (abs(p - a[v]) != 1) {
                    cout << "No\n";
                    return 0;
                }
            } else if (!vis[v]) {
                a[v] = p + 1;
                num[v] = true;
                pq.push({a[v], v});
            }
        }
    }

    cout << "Yes\n";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << '\n';
    }
    return 0;
}