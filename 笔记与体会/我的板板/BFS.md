# BFS 最短路（网格图）模板笔记（C++）
> 基于你提供的逐层 BFS 代码整理，修复小问题，补充标准模板与变体
> 适用：二维网格 4 方向移动、每步代价相同的最短路/最少步数

## 1. 代码在做什么
- n×m 网格，`g[i][j] == -1` 表示障碍物
- 从 `(0,0)` 出发，上下左右移动，求到 `(n-1, m-1)` 的最少步数；不可达输出 `-1`
- 核心技巧：**逐层 BFS** —— `move` 把"当前层"搬到 `b`，`a` 清空后装"下一层"，外层循环的 `step` 天然就是步数

## 2. 逐层 BFS 核心技巧（你代码的精髓）
```cpp
vector<PII> a = {{0,0}};                // 当前层的点
for(int step=0; !a.empty(); step++) {
    auto b = move(a);                   // b 拿走当前层，a 被清空，用来装下一层
    for(auto [x,y] : b) {
        if(x==n-1 && y==m-1) { ans = step; break; }
        for(int i=0; i<4; i++) {
            int xx=x+dx[i], yy=y+dy[i];
            if(xx<0||xx>=n||yy<0||yy>=m) continue;   // 越界
            if(vis[xx][yy] || g[xx][yy]==-1) continue; // 已访问/障碍
            vis[xx][yy] = true;
            a.push_back({xx,yy});       // 放进下一层
        }
    }
    if(ans != -1) break;
}
```
**原理**：第 `step` 次循环处理的点，离起点恰好 `step` 步。因此**第一次碰到终点时的 step 就是最短路**——这正是 BFS 正确性的来源。

## 3. 标准队列版 BFS（最通用）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m;
int g[N][N], dist[N][N];
int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};
queue<pair<int,int>> q;

int bfs() {
    if(g[0][0] == -1) return -1;                 // 起点障碍
    memset(dist, -1, sizeof dist);
    dist[0][0] = 0;
    q.push({0,0});
    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        if(x==n-1 && y==m-1) return dist[x][y];
        for(int i=0; i<4; i++) {
            int xx=x+dx[i], yy=y+dy[i];
            if(xx<0 || xx>=n || yy<0 || yy>=m) continue;      // 越界
            if(g[xx][yy]==-1 || dist[xx][yy]!=-1) continue;   // 障碍/已访问
            dist[xx][yy] = dist[x][y] + 1;
            q.push({xx,yy});
        }
    }
    return -1;   // 不可达
}
```
用 `dist` 数组同时承担"距离"和"是否访问过"两个职责（`-1` = 未访问），比单独开 `vis` 更省。

## 4. 必背关键点
1. **vis/dist 必须在入队（push）时标记**，不能出队时才标——否则同一层节点会重复入队，正确性和复杂度都会炸
2. 三连判断顺序：越界 → 障碍/已访问 → 入队
3. BFS 只适用于**无权图**（每步代价相同）；代价不同要用 Dijkstra / 01-BFS
4. 复杂度：时间 O(n·m)，空间 O(n·m)

## 5. 变体拓展（记个名字，用到再展开）
- **记录路径**：`pre[x][y]` 存"从哪个点走来的"，到终点后倒推回溯输出
- **多源 BFS**：起点有多个，全部初始入队、dist 置 0，常用于"最近着火点/最近水源"类题
- **状态 BFS**：一个点可能走多次（如开关门、拿钥匙），`vis` 加维度：`vis[x][y][state]`
- **01-BFS**：步数代价有 0 有 1，用双端队列，0 走队头 1 走队尾