#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const int maxn = 3e5 + 7;

struct _Q_ {
    int id;
    ll k;
} q[maxn];

struct _function_ {
    int l, r;
    ll x;
} f[maxn];

ll c[maxn];
int lowbit(int x) {
    return x & -x;
}
void add(int pos, ll x) {
    for (; pos < maxn; pos += lowbit(pos)) {
        c[pos] += x;
    }
}
ull query(int pos) {
    ull res = 0;
    for (; pos > 0; pos -= lowbit(pos)) {
        res += c[pos];
    }
    return res;
}

vector<int> pos[maxn];
int a[maxn];
int ans[maxn];
int n, m, k;

ull ss(int i) {
    ull res = 0;
    for (auto x : pos[i]) {
        if (query(x) > 1e18) return 1e18 + 7;
        res += query(x);
    }
    return res;
}

_Q_ lq[maxn], rq[maxn];

void solve(int qL, int qR, int tL, int tR) {
    if (qL > qR || tL > tR) {
        return;
    }

    if (tL == tR) {
        for (int i = qL; i <= qR; ++i) {
            ans[q[i].id] = tL;
        }
        return;
    }

    int mid = tL + (tR - tL) / 2;
    int lc = 0, rc = 0;

    for (int i = tL; i <= mid; ++i) {
        if (f[i].l <= f[i].r) {
            add(f[i].l, f[i].x);
            add(f[i].r + 1, -f[i].x);
        } else {
            add(1, f[i].x);
            add(f[i].r + 1, -f[i].x);
            add(f[i].l, f[i].x);
        }
    }

    for (int i = qL; i <= qR; ++i) {
        ull sum = ss(q[i].id);
        if (sum < q[i].k) {
            q[i].k -= sum;
            rq[rc++] = q[i];
        } else {
            lq[lc++] = q[i];
        }
    }
    for (int i = tL; i <= mid; ++i) {
        if (f[i].l <= f[i].r) {
            add(f[i].l, -f[i].x);
            add(f[i].r + 1, f[i].x);
        } else {
            add(1, -f[i].x);
            add(f[i].r + 1, f[i].x);
            add(f[i].l, -f[i].x);
        }
    }
    for (int i = 0; i < lc; ++i) q[qL + i] = lq[i];
    for (int i = 0; i < rc; ++i) q[qL + lc + i] = rq[i];
    solve(qL, qL + lc - 1, tL, mid);
    solve(qL + lc, qR, mid + 1, tR);
}
void in() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> q[i].k;
        q[i].id = i;
    }
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        cin >> f[i].l >> f[i].r >> f[i].x;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    solve(1, n, 1, k + 1);
    for (int i = 1; i <= n; ++i) {
        if (ans[i] > k) {
            cout << "NIE\n";
        } else {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}
