# Kruskal

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5+5;

struct Edge{int u,v,w;} edge[N];
bool cmp(Edge a, Edge b) {return a.w < b.w;}
int s[N];
int find_set(int x) {
    if(x != s[x]) {
        s[x] = find_set(s[x]);
    }
    return s[x];
}
int n, m;
vector<Edge> Kruskal() {
    sort(edge, edge+m, cmp);
    for(int i=1; i<=n; i++) s[i] = i;
    int sum = 0, cnt = 0;
    vector<Edge> ku;
    for(int i=0; i<m; i++) {
        if(cnt == n-1) break;
        int e1 = find_set(edge[i].u);
        int e2 = find_set(edge[i].v);
        if(e1 == e2) continue;

        ku.push_back(edge[i]);
        sum += edge[i].w;
        s[e1] = e2;
        cnt++;
    }

    if(cnt == n-1) cout << sum << '\n'; // 边总和
    else cout << "orz\n"; // 图不连通
    return ku;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i=0; i<m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    vector<Edge> ans = Kruskal();
    return 0;
}
```