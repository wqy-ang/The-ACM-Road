// 2026-07-07
// Critical Hit（求期望的一道题目）
// https://atcoder.jp/contests/abc280/tasks/abc280_e

#include <bits/stdc++.h>
#define int long long
using namespace std;

const long long mod = 998244353;

// 快速幂
int qpow(int x, int y) {
    int a = 1;
    while (y) {
        if (y & 1)
            a = (a * x) % mod;
        x = (x * x) % mod;
        y >>= 1;
    }
    return a;
}

signed main() {
    int n, p, q;
    cin >> n >> p;

    p = p*qpow(100, mod - 2) % mod;
    q = (mod + 1 - p) % mod;

    vector<int> dp(n + 2, 0);
    for (int i = n - 1; i >= 0; i--) {
        // 状态转移方程
        dp[i] = (1 + q * dp[i + 1] % mod + p * dp[i + 2] % mod) % mod;
    }

    cout << dp[0] << '\n';

    return 0;
}