# 组合 & 全排列 DFS 模板（C++）
> 源码来自你提供的代码，修正其中bug，整理成竞赛可用模板笔记
> 头文件：`#include <bits/stdc++.h>`，适合 ICPC / CCPC / 蓝桥

## 要点说明
1. `#define int long long` 防止数值溢出，`signed main()` 配套
2. 全排列：DFS + `vis` 标记元素是否已选，输出所有排列
3. 原代码**组合函数存在严重bug**：组合dfs里面错误调用了`dfs_fp`，下面给出修复版本
4. 适用范围：n 很小（n ≤ 12 左右），暴力枚举，n大不能用（阶乘爆炸）
5. 数组大小：`N=1e5+5` 足够，`vis` 全局bool数组

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 5;
int n;
vector<vector<int>> all_path; // 存储全部结果
vector<int> path;             // 当前路径
vector<bool> vis(N);

// ========== 全排列 DFS ==========
// a:原始数组，i:当前填到第i个位置
void dfs_perm(vector<int> &a, int i) {
    if (i == n) {
        all_path.push_back(path);
        return;
    }
    for (int j = 0; j < n; j++) {
        if (!vis[j]) {
            vis[j] = true;
            path[i] = a[j];
            dfs_perm(a, i + 1);
            vis[j] = false;
        }
    }
}

// ========== 组合 DFS（选m个元素，不考虑顺序） ==========
// a:原始数组，start:从start下标开始选（保证不重复组合），cnt:已选数量，m:总共要选m个
vector<vector<int>> all_comb;
vector<int> comb;
void dfs_comb(vector<int> &a, int start, int cnt, int m) {
    if (cnt == m) {
        all_comb.push_back(comb);
        return;
    }
    // 组合核心：j从start开始，避免 [1,2] [2,1] 重复
    for (int j = start; j < n; j++) {
        if (!vis[j]) {
            vis[j] = true;
            comb.push_back(a[j]);
            dfs_comb(a, j + 1, cnt + 1, m);
            comb.pop_back();
            vis[j] = false;
        }
    }
}

signed main() {
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    path.resize(n);

    // 1. 求全排列示例
    fill(vis.begin(), vis.end(), false);
    dfs_perm(a, 0);
    cout << "全排列结果：\n";
    for (auto &v : all_path) {
        for (auto x : v) cout << x << " ";
        cout << "\n";
    }

    // 2. 求组合示例：选m=2个
    /*
    int m = 2;
    fill(vis.begin(), vis.end(), false);
    dfs_comb(a, 0, 0, m);
    cout << "组合C(n,2)结果：\n";
    for (auto &v : all_comb) {
        for (auto x : v) cout << x << " ";
        cout << "\n";
    }
    */
    return 0;
}
```

## 📖 模板使用说明
### 全排列 dfs_perm
- 作用：枚举数组所有排列，顺序不同视为不同方案
- 终止条件：`i == n`，填满path
- 标记：`vis[j]`标记下标j的元素是否已经选用

### 组合 dfs_comb
- 作用：从n个元素选出m个，集合不区分顺序
- 终止条件：`cnt == m`，选够m个元素
- 关键：`j从start`开始，下一层`start=j+1`，保证不重复选取

## ⚠️ 复杂度警告（竞赛重点）
- 全排列复杂度：$O(n!)$
  - n=10：3628800，勉强可跑
  - n=12：479001600，大概率TLE
- 组合复杂度：$O(C_n^m)$
> 只能用于小n暴力枚举，大数据不能用！


## ✅ 新增：字典序相关函数笔记
> 头文件：`<algorithm>`，`bits/stdc++.h`已经包含
> 作用：按**字典序**生成排列，竞赛高频，比手写DFS全排列短很多

### 1. next_permutation
```cpp
bool next_permutation(it_begin, it_end);
```
功能：把区间 `[begin,end)` 的序列**变成下一个字典序更大的排列**
- 返回值：
  - `true`：成功找到下一个排列，并原地修改数组
  - `false`：当前已经是字典序最大排列（降序），无法继续，数组会被改成最小排列
- ⚠️ 关键点：
  - **想要枚举全部排列，必须先 sort 升序**！否则只会从当前序列往后枚举
  - 会自动去重：数组有重复元素时，不会生成重复排列（这点比手写DFS省心）
- 示例代码
```cpp
vector<int> v = {1,2,3};
sort(v.begin(),v.end());
do{
    // 处理当前v
}while(next_permutation(v.begin(),v.end()));
```

### 2. prev_permutation
```cpp
bool prev_permutation(it_begin, it_end);
```
功能：把区间 `[begin,end)` 的序列**变成上一个字典序更小的排列**
- 返回值：
  - `true`：找到前一个更小排列，原地修改
  - `false`：当前已经是字典序最小排列（升序），无法继续
- ⚠️ 关键点：
  - 如果要枚举全部排列，**初始数组要降序排序**
```cpp
vector<int> v = {3,2,1};
sort(v.rbegin(),v.rend());
do{
    //处理v
}while(prev_permutation(v.begin(),v.end()));
```