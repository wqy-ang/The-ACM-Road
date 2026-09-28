#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5+5;
// 前后缀和中，数组下标从 1 开始
vector<int> a(N);

void this_is_pre(int n) {
    // 下标 1 ~ base : 前 i 个数的和
    vector<int> pre(n+1);
    pre[0] = 0;
    for(int i=1; i<=n; i++) {
        pre[i] = pre[i-1] + a[i];
    }
    // 区间[l,r]和表示
    int r, l;
    int qslr = pre[r]-pre[l-1];
}

void this_is_suf(int n) {
    // 下标 0 ~ base-1 : i 到 base-1 的和
    vector<int> suf(n+2);
    suf[n+1] = 0;
    for(int i=n; i>=1; i--) {
        suf[i] = suf[i+1] + a[i];
    }
    // 区间[l,r]和表示
    int r, l;
    int qslr = suf[l]-suf[r+1];
}