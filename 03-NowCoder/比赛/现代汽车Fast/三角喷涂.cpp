// 2026-07-16
// https://acexam.nowcoder.com/coding/?uid=EA95895BF192DAE1&qid=11624189
#include<bits/stdc++.h>
#define int long long
using namespace std;

void go() {
    int n, m;
    cin >> n >> m;
    vector<int> b(n+3, 0); // 二阶差分数组 n+3 防止溢出
    int l, r;
    for(int i=0; i<m; i++) {
        cin >> l >> r;
        int c = r-l;
        int mid = (l + r) / 2;
        if(c & 1) {
            b[l]++;
            b[mid+1]--;
            b[mid+2]--;
            b[r+2]++; // 注意：是 r+2
        }
        else {
            b[l]++;
            b[mid+1]-=2;
            b[r+2]++;
        }
    }

    int sa = 0, sb = 0;
    for(int i=1; i<=n; i++) {
        sb += b[i]; // 一阶前缀和
        sa += sb; // 二阶前缀和
        if(i != 1) cout << ' ';
        cout << sa;
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t--) go();
    return 0;
}