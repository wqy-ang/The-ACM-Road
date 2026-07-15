# [ARC063C] Integers on a Tree

> 题目来源：AtCoder Regular Contest 063
> 原题链接：https://atcoder.jp/contests/arc063/tasks/arc063_c

## 题目描述

有一棵包含 $N$ 个顶点的树，顶点编号为 $1, 2, \ldots, N$。第 $i$ 条边（$1 \leq i \leq N-1$）连接了顶点 $A_i$ 和顶点 $B_i$。

高桥君在树上的 $K$ 个顶点上写下了整数。具体来说，对于每个 $1 \leq j \leq K$，他在顶点 $V_j$ 上写下了整数 $P_j$。之后，高桥君开始打瞌睡了。

青木君发现了这棵树，他想在剩下的所有顶点上写下整数，以此来让高桥君吃惊。要让高桥君吃惊，树需要满足以下条件：

- 条件：对于每一条边直接相连的两个顶点，它们上面写的整数之差恰好为 $1$。

请判断是否可以通过巧妙地在剩余顶点上写下整数，使得整棵树满足上述条件。如果可以，请给出一种具体的写法。

## 输入格式

输入以如下格式从标准输入读入。

> $N$ $A_1$ $B_1$ $A_2$ $B_2$ $\ldots$ $A_{N-1}$ $B_{N-1}$ $K$ $V_1$ $P_1$ $V_2$ $P_2$ $\ldots$ $V_K$ $P_K$

## 输出格式

如果可以通过在剩余顶点上写下整数使得树满足条件，则输出 `Yes`，否则输出 `No`。

如果满足条件，还需额外输出 $N$ 行。第 $v$ 行（$1 \leq v \leq N$）输出写在顶点 $v$ 上的整数。若存在多种满足条件的写法，输出其中任意一种即可。

## 解题思路
本题可以通过**多源扩展 + 小根堆优先队列**的思路求解，本质是从所有已确定数值的节点出发，按照「相邻节点数值差为 1」的规则向外逐层填充，并实时校验约束冲突。

### 核心算法流程
1. 使用邻接表存储树的边关系。
2. 初始化小根堆（按节点数值升序排列），将所有已给定数值的节点入堆，并标记为「已赋值」。
3. 不断从堆顶取出数值最小的节点，标记为「已处理」，然后遍历其所有邻接节点：
   - 若邻接节点已处理，直接跳过。
   - 若邻接节点已赋值但未处理：校验两节点数值差是否为 1，不满足则直接判定无解并退出。
   - 若邻接节点未赋值：将其数值设为当前节点数值 + 1，标记为已赋值并入堆。
4. 若完整扩展完所有节点且无冲突，则输出 `Yes` 与最终方案。

### 初始实现的缺陷与修正
#### 问题表现
最初的实现将「访问标记」在节点入队时设置，并对所有已访问的邻接节点都执行差值校验，存在两处问题：
1. **冗余校验**：同一条边的两个端点会互相重复检查，产生不必要的判断开销。
2. **冲突漏检**：入队即标记为已访问，会导致节点在被真正处理前，无法被其他相邻的已赋值节点校验，可能遗漏约束冲突。

#### 修正方案
- 拆分两类标记：`num[]` 标记节点是否已被赋值，`vis[]` 标记节点是否已弹出队列并完成处理。
- 仅对「已赋值但未处理」的邻接节点做差值校验，避免重复检查已处理完成的边。
- 将 `vis[u] = true` 放在节点**弹出队列之后**执行，保证节点在入队后、处理前仍可被相邻节点校验。

## 代码实现

### 初始版本（存在缺陷）
```cpp
#include <bits/stdc++.h>
#define int long long
#define PII pair<int, int>
using namespace std;

const int N = 1e5 + 5;
vector<int> e[N], a(N);
vector<bool> vis(N);

signed main() {
    int n; cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    priority_queue<PII, vector<PII>, greater<PII>> pq;
    bool ok = true;
    int k; cin >> k;
    for(int i = 0; i < k; i++) {
        int v, p; cin >> v >> p;
        a[v] = p;
        vis[v] = true;
        pq.push({p, v});
    }

    while(!pq.empty()) {
        auto [p, u] = pq.top();
        pq.pop();
        for(int &v : e[u]) {
            if(vis[v]) {
                if(abs(a[v] - p) != 1) {
                    ok = false;
                    break;
                }
                continue;
            }
            vis[v] = true;
            a[v] = p + 1;
            pq.push({a[v], v});
        }
    }

    if(ok) {
        cout << "Yes\n";
        for(int i = 1; i <= n; i++) {
            cout << a[i] << '\n';
        }
    } else {
        cout << "No\n";
    }
    return 0;
}
```

### 修正版本（推荐）
```cpp
#include <bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define QwQ cin.tie(0)->sync_with_stdio(0);
using namespace std;

const int N = 1e5 + 5;
vector<int> e[N], a(N);
vector<bool> vis(N), num(N);

signed main() {
    QwQ
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    priority_queue<PII, vector<PII>, greater<PII>> pq;
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int v, p;
        cin >> v >> p;
        a[v] = p;
        num[v] = true;
        pq.push({p, v});
    }

    while (!pq.empty()) {
        auto [p, u] = pq.top();
        pq.pop();
        vis[u] = true;
        for (int &v : e[u]) {
            if (!vis[v] && num[v]) {
                // 已赋值但未处理的邻接点，校验约束
                if (abs(p - a[v]) != 1) {
                    cout << "No\n";
                    return 0;
                }
            } else if (!vis[v]) {
                // 未赋值节点，填充数值并入队
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
```

### 关键注意点
> 节点的「已处理标记」在**弹出队列时**设置，而非入队时设置。这是保证冲突校验完整、不遗漏的核心细节。

---
