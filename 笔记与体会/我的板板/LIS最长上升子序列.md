# 最长上升序列(LIS)

## 返回长度的板板

### 二重循环
```cpp
int length_LIS(vector<int> &nums) {
    int n = nums.size();
    vector<int> f(n, 1);
    int ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                f[i] = max(f[i], f[j]+1);
            }
        }
        ans = max(ans, f[i]);
    }
    return ans;
    // return ranges::max(f);
}
```

### 贪心 + 二分
```cpp
int length_LIS(vector<int> &nums) {
    vector<int> g;
    for (int x : nums) {
        auto it = lower_bound(g.begin(), g.end(), x);
        if (it == g.end()) {
            g.push_back(x); // >=x 的 g[j] 不存在
        } else {
            *it = x;
        }
    }
    return g.size();
}
```

## 返回序列的板板

### 板板代码
```cpp
vector<int> vec_LIS(vector<int> &nums) {
    if (nums.empty()) {
        return {};
    }
    int n = nums.size();
    vector<pair<int, int>> g; // (value, index)
    vector<int> last(n, -1);  // last[i]：nums[i]在LIS中的前驱下标

    for (int i = 0; i < n; i++) {
        int x = nums[i];
        auto it = lower_bound(g.begin(), g.end(), make_pair(x, -1));
        int j = it - g.begin();
        if (j > 0) {
            last[i] = g[j - 1].second;
        }
        if (j < g.size()) {
            g[j] = {x, i};
        } else {
            g.emplace_back(x, i);
        }
    }

    vector<int> lis;
    for (int i = g.back().second; i >= 0; i = last[i]) {
        lis.push_back(nums[i]);
    }
    reverse(lis.begin(), lis.end());
    return lis;
}
```