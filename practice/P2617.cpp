#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
struct _function_ {
    int id;
    int pos, data, wei;
    int l, r, k;
    int type;
} q[maxn * 3];
int ans[maxn * 3];
int t[maxn];
int lowbit(int pos) {
    return pos & -pos;
}
void add(int pos, int x) {
    while (pos <= 1e5) {
        t[pos] += x;
        pos += lowbit(pos);
    }
    return;
}
int sum(int pos) {
    int res = 0;
    while (pos) {
        res += t[pos];
        pos -= lowbit(pos);
    }
    return res;
}
int query(int l, int r) {
    return sum(r) - sum(l - 1);
}
int cur[maxn << 1], cnt;
struct _st_ {
    vector<_function_> s[maxn << 3];
    int ls(int p) {
        return p << 1;
    }
    int rs(int p) {
        return p << 1 | 1;
    }
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            s[1].push_back(q[i]);
        }
        return;
    }
    void work(int p, int l, int r) {
        if (s[p].empty())
            return;
        if (l == r) {
            for (auto x : s[p]) {
                if (x.type == 2) {
                    ans[x.id] = cur[l];
                }
            }
            return;
        }
        int mid = (l + r) >> 1;
        for (auto x : s[p]) {
            if (x.type == 1) {
                if (x.data <= mid) {
                    add(x.pos, x.wei);
                    s[ls(p)].push_back(x);
                } else {
                    s[rs(p)].push_back(x);
                }
            } else if (x.type == 2) {
                int ss = query(x.l, x.r);
                if (x.k > ss) {
                    x.k -= ss;
                    s[rs(p)].push_back(x);
                } else {
                    s[ls(p)].push_back(x);
                }
            }
        }
        for (auto x : s[p]) {
            if (x.type == 1) {
                if (x.data <= mid) {
                    add(x.pos, -x.wei);
                }
            }
        }
        s[p].clear();
        work(ls(p), l, mid);
        work(rs(p), mid + 1, r);
        return;
    }
} st;
int n, m, len;

int a[maxn];

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cur[++cnt] = a[i];
    }
    for (int i = 1; i <= n; ++i) {
        q[i] = {i, i, a[i], 1, 0, 0, 0, 1};
    }
    len = n;
    for (int i = 1; i <= m; ++i) {
        char c;
        cin >> c;
        if (c == 'C') {
            int x, y;
            cin >> x >> y;
            cur[++cnt] = y;
            len++;
            q[len] = {len, x, a[x], -1, 0, 0, 0, 1};
            a[x] = y;
            len++;
            q[len] = {len, x, y, 1, 0, 0, 0, 1};
        }
        if (c == 'Q') {
            int l, r, k;
            cin >> l >> r >> k;
            len++;
            q[len] = {len, 0, 0, 0, l, r, k, 2};
        }
    }
    sort(cur + 1, cur + cnt + 1);
    cnt = unique(cur + 1, cur + cnt + 1) - cur - 1;
    for (int i = 1; i <= len; ++i) {
        if (q[i].type == 1) {
            q[i].data = lower_bound(cur + 1, cur + cnt + 1, q[i].data) - cur;
        }
    }
    return;
}

int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    st.init(len);
    st.work(1, 1, cnt);
    for (int i = 1; i <= len; ++i) {
        if (q[i].type == 2) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}