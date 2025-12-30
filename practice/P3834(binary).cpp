#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
struct _question_ {
    int l, r, k;
    int id, type;
} q[maxn];
struct node {
    int data, id;
} a[maxn];
// bit
int c[maxn];
int lowbit(int p) {
    return p & -p;
}
void add(int pos, int x) {
    while (pos <= 2e5) {
        c[pos] += x;
        pos += lowbit(pos);
    }
    return;
}
int query(int pos) {
    int res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
// end bit
int n, m;
int ans[maxn];
struct _st_ {
    vector<_question_> s[maxn << 2];
    int ls(int p) {
        return p << 1;
    }
    int rs(int p) {
        return p << 1 | 1;
    }
    void init() {
        for (int i = 1; i <= m; ++i) {
            s[1].push_back(q[i]);
        }
        return;
    }
    void work(int p, int l, int r) {
        if (l == r) {
            for (auto x : s[p]) {
                ans[x.id] = a[l].data;
            }
            return;
        }
        const int mid = (l + r) >> 1;
        for (int i = l; i <= mid; ++i) {
            add(a[i].id, 1);
        }
        for (auto x : s[p]) {
            int ss = query(x.r) - query(x.l - 1);
            if (x.k > ss) {
                x.k -= ss;
                s[rs(p)].push_back(x);
            } else {
                s[ls(p)].push_back(x);
            }
        }
        for (int i = l; i <= mid; ++i) {
            add(a[i].id, -1);
        }
        s[p].clear();
        work(ls(p), l, mid);
        work(rs(p), mid + 1, r);
        return;
    }
} st;

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].data;
        a[i].id = i;
    }
    sort(a + 1, a + n + 1, [](const node &a, const node &b) { return a.data < b.data; });
    for (int i = 1; i <= m; ++i) {
        cin >> q[i].l >> q[i].r >> q[i].k;
        q[i].id = i;
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    st.init();
    st.work(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}