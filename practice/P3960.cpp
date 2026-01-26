#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 3e5 + 7;
int n, m, q;

struct segtree {
    struct node {
        int l, r;
        int data;
    } s[maxn << 7];
    int root[maxn], cnt;
    void add(int &p, int l, int r, int pos) {
        if (!p)
            p = ++cnt;
        if (l == r) {
            s[p].data = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            add(s[p].l, l, mid, pos);
        else
            add(s[p].r, mid + 1, r, pos);
        s[p].data = s[s[p].l].data + s[s[p].r].data;
        return;
    }
    int query(int &p, int l, int r, int d) {
        if (!p)
            p = ++cnt;
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        int sum = (mid - l + 1) - s[s[p].l].data;
        if (d <= sum)
            return query(s[p].l, l, mid, d);
        else
            return query(s[p].r, mid + 1, r, d - sum);
    }
} tree;
vector<ll> sum[maxn];
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m >> q;
    for (int i = 1, x, y; i <= q; ++i) {
        cin >> x >> y;
        ll ans;
        if (y < m) {
            int pos = tree.query(tree.root[x], 1, m - 1 + q, y);
            if (pos < m) {
                ans = (x - 1) * 1ll * m * 1ll + pos * 1ll;
            } else {
                ans = sum[x][pos - m];
            }
            sum[n + 1].push_back(ans);
            tree.add(tree.root[x], 1, m - 1 + q, pos);
            pos = tree.query(tree.root[n + 1], 1, n + q, x);
            ll toadd;
            if (pos <= n) {
                toadd = pos * 1ll * m * 1ll;
            } else {
                toadd = sum[n + 1][pos - n - 1];
            }
            sum[x].push_back(toadd);
            tree.add(tree.root[n + 1], 1, n + q, pos);
        } else {
            int pos = tree.query(tree.root[n + 1], 1, n + q, x);
            if (pos <= n) {
                ans = pos * 1ll * m * 1ll;
            } else {
                ans = sum[n + 1][pos - n - 1];
            }
            sum[n + 1].push_back(ans);
            tree.add(tree.root[n + 1], 1, n + q, pos);
        }
        cout << ans << '\n';
    }
    return 0;
}