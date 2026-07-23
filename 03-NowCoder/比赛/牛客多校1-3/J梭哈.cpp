#include <bits/stdc++.h>
#define QwQ cin.tie(0)->sync_with_stdio(0);
#define all(A) A.begin(), A.end()
#define rall(A) A.rbegin(), A.rend()
#define PII pair<int, int>
#define ll long long
#define fi first
#define se second
using namespace std;

// 14^5 作为牌型等级的权重，确保高等级牌型得分一定更高
const ll w = 537824LL;
vector<bool> bright;

// 对应牌转化为数字
int puke_tonum(string &s) {
    int p, f;
    switch (s[0]) {
    case 'A':
        p = 13;
        break;
    case 'K':
        p = 12;
        break;
    case 'Q':
        p = 11;
        break;
    case 'J':
        p = 10;
        break;
    case 'T':
        p = 9;
        break;
    case '9':
        p = 8;
        break;
    case '8':
        p = 7;
        break;
    case '7':
        p = 6;
        break;
    case '6':
        p = 5;
        break;
    case '5':
        p = 4;
        break;
    case '4':
        p = 3;
        break;
    case '3':
        p = 2;
        break;
    case '2':
        p = 1;
        break;
    default:
        break;
    }

    switch (s.back()) {
    case 'C':
        f = 1;
        break;
    case 'D':
        f = 2;
        break;
    case 'H':
        f = 3;
        break;
    case 'S':
        f = 4;
        break;
    default:
        break;
    }

    return (p - 1) * 4 + f;
}

// 数字转化为对应牌
PII num_topuke(int i) {
    int p = (i + 3) / 4;
    int f = i % 4;
    if (f == 0)
        f = 4;

    return {p, f};
}

// 计算得分
int cal_soc(vector<int> &a, int c) {
    vector<int> val;    // 牌的点数
    vector<int> flower; // 牌的花色
    for (int &x : a) {
        auto [p, f] = num_topuke(x);
        val.push_back(p);
        flower.push_back(f);
    }
    auto [pc, fc] = num_topuke(c);
    val.push_back(pc);
    flower.push_back(fc);

    sort(all(val));

    // 判断同花
    bool tonhua = true;
    for (int i = 1; i < 5; i++) {
        if (flower[i] != flower[0]) {
            tonhua = false;
            break;
        }
    }
    // 判断顺子
    bool shunzi = false;
    int szh = 0;
    bool has_dup = false;
    for (int i = 1; i < 5; i++) {
        if (val[i] == val[i - 1]) {
            has_dup = true;
            break;
        }
    }
    if (!has_dup) {
        if (val[4] - val[0] == 4) {
            shunzi = true;
            szh = val[4];
        } else if (val[4] == 13 && val[0] == 1) {
            if (val[1] == 2 && val[2] == 3 && val[3] == 4) {
                shunzi = true;
                szh = 4;
            }
        }
    }

    map<int, int> mp;
    for (int &x : val)
        mp[x]++;
    vector<PII> puke; // <数量，牌点数>
    for (auto [u, v] : mp) {
        puke.push_back({v, u});
    }
    sort(rall(puke));

    // 同花顺
    if (tonhua && shunzi) {
        return 8 * w + szh;
    }

    // 四条
    if (puke[0].fi == 4) {
        return 7 * w + 14 * puke[0].se + puke[1].se;
    }

    // 3带2
    if (puke[0].fi == 3 && puke[1].fi == 2) {
        return 6 * w + 14 * puke[0].se + puke[1].se;
    }

    // 同花
    if (tonhua) {
        int res = 5 * w;
        res += val[4] * 38416; // 14^4
        res += val[3] * 2744;  // 14^3
        res += val[2] * 196;   // 14^2
        res += val[1] * 14;    // 14^1
        res += val[0];
        return res;
    }

    // 顺子
    if (shunzi) {
        return 4 * w + szh;
    }

    // 三条
    if (puke[0].fi == 3) {
        return 3 * w + 196 * puke[0].se + 14 * puke[1].se + puke[2].se;
    }

    // 两对
    if (puke[0].fi == 2 && puke[1].fi == 2) {
        int big = max(puke[0].second, puke[1].second);
        int small = min(puke[0].second, puke[1].second);
        return 2 * w + big * 196 + small * 14 + puke[2].second;
    }

    // 一对
    if (puke[0].fi == 2) {
        return w + 2744 * puke[0].se + 196 * puke[1].se + 14 * puke[2].se +
               puke[3].se;
    }

    return 38416 * val[4] + 2744 * val[3] + 196 * val[2] + 14 * val[1] + val[0];
}

void go() {
    bright.assign(53, false);
    vector<int> tiger;
    vector<int> piks;
    for (int i = 0; i < 8; i++) {
        string s;
        cin >> s;
        int pai = puke_tonum(s);
        bright[pai] = true;
        if (i < 4)
            tiger.push_back(pai);
        else
            piks.push_back(pai);
    }

    // 遍历所有暗牌，生成二者的可能得分
    vector<int> tiger_soc(53, 0);
    vector<int> piks_soc(53, 0);
    for (int i = 1; i <= 52; i++) {
        if (bright[i])
            continue;

        int ti_s = cal_soc(tiger, i);
        int pi_s = cal_soc(piks, i);

        tiger_soc[i] = ti_s;
        piks_soc[i] = pi_s;
    }

    bool ti_win = true;
    for (int i = 1; i <= 52; i++) {
        if (bright[i])
            continue;
        int x = piks_soc[i];
        int ti_mx = 0;
        for (int j = 1; j <= 52; j++) {
            if (bright[j])
                continue;
            if (i == j)
                continue;

            ti_mx = max(ti_mx, tiger_soc[j]);
        }
        if (x >= ti_mx) {
            ti_win = false;
            break;
        }
    }
    if (ti_win) {
        cout << "WoYaoYanPai\n";
        return;
    }

    bool pi_win = false;
    for (int i = 1; i <= 52; i++) {
        if (bright[i])
            continue;
        int x = piks_soc[i];
        int ti_mx = 0;
        for (int j = 1; j <= 52; j++) {
            if (bright[j])
                continue;
            if (i == j)
                continue;

            ti_mx = max(ti_mx, tiger_soc[j]);
        }
        if (x > ti_mx) {
            pi_win = true;
            break;
        }
    }
    if (pi_win) {
        cout << "GeiWoCaPiXie\n";
        return;
    }

    cout << "PaiMeiYouWenTi\n";
}

int main() {
    QwQ int t = 1;
    cin >> t;
    while (t--) {
        go();
    }
}