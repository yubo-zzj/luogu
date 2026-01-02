#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 7;
struct node {
    ll d, p, l;
} a[maxn];
int n, m;
struct _segtree_ {
    struct node {
        int ls, rs;
        ll sumw, suml;
    };
    node s[maxn << 6];
    int cnt;
    int root[maxn];
    // void build(int &p, int l, int r) {
    //     if (!p)
    //         p = ++cnt;
    //     if (l == r)
    //         return;
    //     int mid = (l + r) >> 1;
    //     build(s[p].ls, l, mid);
    //     build(s[p].rs, mid + 1, r);
    //     return;
    // }
    int add(int p, int l, int r, ll x, ll y) {
        int rt = ++cnt;
        s[rt] = s[p];
        s[rt].suml += y;
        s[rt].sumw += x * y;
        if (l != r) {
            int mid = (l + r) >> 1;
            if (x <= mid)
                s[rt].ls = add(s[rt].ls, l, mid, x, y);
            else
                s[rt].rs = add(s[rt].rs, mid + 1, r, x, y);
        }
        return rt;
    }
    ll query(int p, int l, int r, ll k) {
        if (l == r) {
            return l * k;
        }
        int mid = (l + r) >> 1;
        if (s[s[p].ls].suml >= k) {
            return query(s[p].ls, l, mid, k);
        } else {
            return s[s[p].ls].sumw + query(s[p].rs, mid + 1, r, k - s[s[p].ls].suml);
        }
    }
    void init() {
        // build(root[0], 1, 1e5);
        // cout << root[0] << ' '; 
        for (int i = 1; i <= n; ++i) {
            root[i] = add(root[i - 1], 1, 1e5, a[i].p, a[i].l);
        }
        // for (int i = 1; i <= n; ++i) {
        //     cout << root[i] << ' '; 
        // }
        return;
    }
} st;

void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].d >> a[i].p >> a[i].l;
    }
    a[0].d = -1;
    sort(a + 1, a + n + 1, [](const node &a, const node &b) { return a.d > b.d; });
    return;
}

int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    st.init();
    while (m--) {
        ll g, L;
        cin >> g >> L;
        int ans = 0;
        int l = 1, r = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            ll res = st.query(st.root[mid], 1, 1e5, L);
            if (res <= g && st.s[st.root[mid]].suml >= L) {
                ans = mid;
                r = mid - 1;
            } else
                l = mid + 1;
        }
        cout << a[ans].d << '\n';
    }
    return 0;
}