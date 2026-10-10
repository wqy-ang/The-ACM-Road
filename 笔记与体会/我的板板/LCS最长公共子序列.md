# 最长公共子序列(LCS)

## 返回长度板板

### 二维写法代码
```cpp
int LCS(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }

    return dp[n][m];
}
```

### 一维写法代码
```cpp
int LCS(string s1, string s2) {
    if (s1.size() < s2.size()) swap(s1, s2);
    int n = s1.size(), m = s2.size();
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        int pre = 0; // pre保存dp[i-1][j-1]
        for (int j = 1; j <= m; j++) {
            int tmp = dp[j]; // tmp 记录旧 dp[j] = dp[i-1][j]
            if (s1[i - 1] == s2[j - 1]) {
                dp[j] = pre + 1;
            } else {
                dp[j] = max(dp[j], dp[j - 1]);
            }
            pre = tmp; // 把旧dp[j]交给pre，作为下一轮j+1的左上角dp[i-1][j]
        }
    }
    return dp[m];
}
```

## 返回子序列串板板代码
```cpp
string LCS_string(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> b(n + 1, vector<int>(m + 1, 0)); // 初始化0

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                b[i][j] = 1; // 斜向
            } else {
                if (dp[i][j - 1] >= dp[i - 1][j]) {
                    dp[i][j] = dp[i][j - 1];
                    b[i][j] = 2; // 左
                } else {
                    dp[i][j] = dp[i - 1][j];
                    b[i][j] = 3; // 上
                }
            }
        }
    }
    if (dp[n][m] == 0) return ""; // 无公共子序列返回空串

    string ans;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (b[i][j] == 1) {
            ans += s1[i - 1];
            i--; j--;
        } else if (b[i][j] == 2) {
            j--;
        } else if (b[i][j] == 3) {
            i--;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
```