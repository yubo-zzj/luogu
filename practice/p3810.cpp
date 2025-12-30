#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
const int maxs = 2e5 + 7;
struct node {
    int a, b, c;
    int ans = 0, sum;
    bool operator!=(const node &x) {
        if (this->a != x.a)
            return 1;
        if (this->b != x.b)
            return 1;
        if (this->c != x.c)
            return 1;
        return 0;
    }
} a[maxn];
struct _treearry_ {
    int lowbit(int x) {
        return x & -x;
    }
    int c[maxs];
    void add(int pos, int x) {
        while (pos <= 2e5) {
            c[pos] += x;
            pos += lowbit(pos);
        }
        return;
    }
    int sum(int x) {
        int res = 0;
        while (x) {
            res += c[x];
            x -= lowbit(x);
        }
        return res;
    }
} treearry;
bool cmp(node x, node y) {
    if (x.a != y.a)
        return x.a < y.a;
    if (x.b != y.b)
        return x.b < y.b;
    return x.c < y.c;
}
bool cmp1(node x, node y) {
    return x.b < y.b;
}
void CDQ(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    sort(a + l, a + mid + 1, cmp1);
    sort(a + mid + 1, a + r + 1, cmp1);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && a[p1].b <= a[p2].b) {
            treearry.add(a[p1].c, a[p1].sum);
            p1++;
        }
        a[p2].ans += treearry.sum(a[p2].c);
        p2++;
    }
    for (int i = l; i < p1; ++i) {
        treearry.add(a[i].c, -a[i].sum);
    }
    return;
}
int n, k;
void in() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].a >> a[i].b >> a[i].c;
    sort(a + 1, a + n + 1, cmp);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    int cnt = 0;
    int wei = 0;
    for (int i = 1; i <= n; ++i) {
        wei++;
        if (a[i] != a[i + 1]) {
            a[++cnt] = a[i];
            a[cnt].sum = wei;
            wei = 0;
        }
    }
    // cout << cnt << endl;
    CDQ(1, cnt);
    int ans[maxn];
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= cnt; ++i) {
        ans[a[i].ans + a[i].sum - 1] += a[i].sum;
    }
    // for(int i = 1; i <= n; ++i) {
    //     cout << a[i].ans << endl;
    // }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}