#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 3e5 + 7;
int root[maxn];
struct segtree {
    int ls[maxn << 6], rs[maxn << 6], s[maxn << 6], cnt;
    void add(int &p, int l, int r, int pos) {
        if (!p)
            p = ++cnt;
        if (l == r) {
            s[p] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            add(ls[p], l, mid, pos);
        else
            add(rs[p], mid + 1, r, pos);
        s[p] = s[ls[p]] + s[rs[p]];
        return;
    }
    int query(int &p, int l, int r, int k) {
        if (!p)
            p = ++cnt;
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        int len = mid - l + 1;
        int sum = len - s[ls[p]];
        if (k <= sum)
            return query(ls[p], l, mid, k);
        else
            return query(rs[p], mid + 1, r, k - sum);
    }
} tree;
int n, m, q;
vector<ll> s[maxn];
int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> q;
    for (int i = 1, x, y; i <= q; ++i) {
        cin >> x >> y;
        ll ans;
        if (y < m) {
            int pos = tree.query(root[x], 1, m - 1 + q, y);
            if (pos < m) {
                ans = (x - 1) * 1ll * m * 1ll + pos * 1ll;
            } else {
                ans = s[x][pos - m];
            }
            tree.add(root[x], 1, m - 1 + q, pos);
            s[n + 1].push_back(ans);
            pos = tree.query(root[n + 1], 1, n + q, x);
            ll sum;
            if (pos <= n) {
                sum = pos * 1ll * m * 1ll;
            } else {
                sum = s[n + 1][pos - n - 1];
            }
            s[x].push_back(sum);
            tree.add(root[n + 1], 1, n + q, pos);
        } else {
            int pos = tree.query(root[n + 1], 1, n + q, x);
            if (pos <= n) {
                ans = pos * 1ll * m * 1ll;
            } else {
                ans = s[n + 1][pos - n - 1];
            }
            s[n + 1].push_back(ans);
            tree.add(root[n + 1], 1, n + q, pos);
        }
        cout << ans << '\n';
    }
    return 0;
}