#include <bits/stdc++.h>
#define snakes pair<int, int>
using namespace std;
inline int read() {
    int s = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        s = s * 10 + (ch ^ 48), ch = getchar();
    return s;
}
const int maxn = 1e6 + 30;
const int inf = 0x3f3f3f3f3f;
snakes qmax[maxn];
int h_mx, t_mx; // 单调增
snakes qmin[maxn];
int h_mn, t_mn; // 单调减
bool empty_mx() {
    return h_mx > t_mx;
} // 单调增是否为空
bool empty_mn() {
    return h_mn > t_mn;
} // 单调减是否为空
snakes topmx() { // 取最大值
    if (empty_mx()) {
        h_mn++;
        return qmin[h_mn - 1];
    } // 单调增空取单调减头
    else if (empty_mn()) {
        t_mx--;
        return qmax[t_mx + 1];
    } // 单调减空取单调增尾
    else if (qmax[t_mx] < qmin[h_mn]) {
        h_mn++;
        return qmin[h_mn - 1];
    } // 增尾大取增尾
    else {
        t_mx--;
        return qmax[t_mx + 1];
    } // 减头大取减头
}
snakes topmn() { // 取最小值
    if (empty_mx()) {
        t_mn--;
        return qmin[t_mn + 1];
    } // 单调增空取单调减尾
    else if (empty_mn()) {
        h_mx++;
        return qmax[h_mx - 1];
    } // 单调减空取单调增头
    else if (qmin[t_mn] < qmax[h_mx]) {
        t_mn--;
        return qmin[t_mn + 1];
    } else {
        h_mx++;
        return qmax[h_mx - 1];
    }
}
snakes MIN(snakes a, snakes b) {
    if (a < b)
        return a;
    else
        return b;
}
int a[maxn];
int t, n;
void init() {
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    memset(qmax, 0, sizeof(qmax));
    memset(qmin, 0, sizeof(qmin));
    h_mx = 1, h_mn = 1, t_mx = 0, t_mn = 0;
    for (int i = 1; i <= n; ++i)
        qmax[++t_mx] = (snakes){a[i], i};
    int flg = 0, tot = 0, dep = 0;
    while (1) {
        ++tot;
        snakes x = topmn(), y = topmx();
        snakes z =
            MIN((empty_mx() ? (snakes){inf, -inf} : qmax[h_mx]), (empty_mn() ? (snakes){inf, -inf} : qmin[t_mn]));
        y.first -= x.first;
        if (y > z || tot == n - 1) {
            if (flg) {
                cout << n - (flg - (dep & 1)) << endl;
                return;
            }
            if (tot == n - 1) {
                cout << 1 << endl;
                return;
            }
            qmin[++t_mn] = y;
        } else {
            dep++;
            if (flg == 0)
                flg = tot;
            qmin[++t_mn] = y;
        }
    }
    return;
}
void work() {
    //	n = read();
    //	for(int i = 1; i <= n; ++i) a[i] = read();
    memset(qmax, 0, sizeof(qmax));
    memset(qmin, 0, sizeof(qmin));
    h_mx = 1, h_mn = 1, t_mx = 0, t_mn = 0;
    for (int i = 1; i <= n; ++i)
        qmax[++t_mx] = (snakes){a[i], i};
    int flg = 0, tot = 0, dep = 0;
    while (1) {
        ++tot;
        snakes x = topmn(), y = topmx();
        snakes z =
            MIN((empty_mx() ? (snakes){inf, -inf} : qmax[h_mx]), (empty_mn() ? (snakes){inf, -inf} : qmin[t_mn]));
        y.first -= x.first;
        if (y > z || tot == n - 1) {
            if (flg) {
                cout << n - (flg - (dep & 1)) << endl;
                return;
            }
            if (tot == n - 1) {
                cout << 1 << endl;
                return;
            }
            qmin[++t_mn] = y;
        } else {
            dep++;
            if (flg == 0)
                flg = tot;
            qmin[++t_mn] = y;
        }
    }
    return;
}
int main() {
    //	freopen("P7078_5.in" , "r", stdin );
    //	freopen("P7078_5.out", "w", stdout);
    t = read();
    init();
    while (--t) {
        int cishu = read();
        for (int i = 1; i <= cishu; ++i) {
            int aa = read();
            a[aa] = read();
        }
        work();
    }
    return 0;
}