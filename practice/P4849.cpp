#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 8e4 + 7;
const int mod = 998244353;
const ll inf = 1e15;
struct monster {
    int h, e, a, d, id;
    ll c;
    int opt; // opt=1->left,opt=2->right
    bool operator!=(const monster &a) {
        if (this->h != a.h)
            return true;
        if (this->e != a.e)
            return true;
        if (this->a != a.a)
            return true;
        if (this->d != a.d)
            return true;
        return false;
    }
} a[maxn], b[maxn], c[maxn];
struct _treearry_ {
    ll c[maxn], time[maxn];
    ll nc, ntime;
    int lowbit(int x) {
        return x & -x;
    }
    void more(int pos, ll x, ll cnt) {
        while (pos <= 8e4) {
            if (x == c[pos])
                time[pos] += cnt;
            if (x > c[pos])
                c[pos] = x, time[pos] = cnt;
            time[pos] %= mod;
            pos += lowbit(pos);
        }
        return;
    }
    void query(int pos) {
        nc = 0, ntime = 0;
        while (pos) {
            if (c[pos] == nc)
                ntime += time[pos];
            if (c[pos] > nc) {
                nc = c[pos];
                ntime = time[pos];
            }
            ntime %= mod;
            pos -= lowbit(pos);
        }
        return;
    }
    void clear(int pos) {
        while (pos <= 8e4) {
            c[pos] = 0;
            time[pos] = 0;
            pos += lowbit(pos);
        }
        return;
    }
} treearry;
ll dp[maxn], cnt[maxn];
bool cmp3(monster a, monster b) { // 按照a排序
    if (a.a != b.a)
        return a.a < b.a;
    return a.id < b.id;
}
void CDQ2(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ2(l, mid);
    for (int i = l; i <= r; ++i)
        c[i] = b[i];
    sort(c + l + 0, c + mid + 1, cmp3);
    sort(c + mid + 1, c + r + 1, cmp3);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && c[p1].a <= c[p2].a) {
            if (c[p1].opt == 1)
                treearry.more(c[p1].d, dp[c[p1].id], cnt[c[p1].id]);
            p1++;
        }
        if (c[p2].opt == 2) {
            treearry.query(c[p2].d);
            if (treearry.nc + a[c[p2].id].c > dp[c[p2].id]) {
                dp[c[p2].id] = treearry.nc + a[c[p2].id].c;
                cnt[c[p2].id] = treearry.ntime;
            } else if (treearry.nc + a[c[p2].id].c == dp[c[p2].id]) {
                cnt[c[p2].id] += treearry.ntime;
            }
        }
        p2++;
    }
    for (int i = l; i < p1; ++i)
        if (c[i].opt == 1)
            treearry.clear(c[i].d);
    CDQ2(mid + 1, r);
    return;
}
bool cmp2(monster a, monster b) { // 按照e排序
    if (a.e != b.e)
        return a.e < b.e;
    return a.id < b.id;
}
void CDQ1(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ1(l, mid);
    for (int i = l; i <= mid; ++i) {
        b[i] = a[i];
        b[i].opt = 1;
    }
    for (int i = mid + 1; i <= r; ++i) {
        b[i] = a[i];
        b[i].opt = 2;
    }
    sort(b + l, b + r + 1, cmp2);
    CDQ2(l, r);
    CDQ1(mid + 1, r);
    return;
}
bool cmp1(monster a, monster b) { // 按照h排序
    if (a.h != b.h)
        return a.h < b.h;
    if (a.e != b.e)
        return a.e < b.e;
    if (a.a != b.a)
        return a.a < b.a;
    return a.d < b.d;
}
int n;
void in() { // 输入+离散化
    int m;
    cin >> n >> m;
    int curd[maxn];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].h >> a[i].e >> a[i].a >> a[i].d >> a[i].c;
        curd[i] = a[i].d;
    }
    sort(curd + 1, curd + n + 1);
    int lend = unique(curd + 1, curd + n + 1) - curd - 1;
    for (int i = 1; i <= n; ++i) {
        a[i].d = lower_bound(curd + 1, curd + lend + 1, a[i].d) - curd;
    }
    return;
}
int init() { // 预处理：去重+继承权值
    sort(a + 1, a + n + 1, cmp1);
    int lena = 1, flg = a[1].c >= 0;
    for (int i = 2; i <= n; ++i) {
        if (a[i] != a[i - 1]) {
            a[++lena] = a[i];
            flg = a[lena].c >= 0;
        } else {
            if (flg) {
                if (a[i].c > 0)
                    a[lena].c += a[i].c;
            } else {
                if (a[i].c >= 0)
                    a[lena] = a[i], flg = 1;
                if (a[i].c < 0)
                    a[lena].c = max(a[lena].c, a[i].c);
            }
        }
    }
    return lena;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    n = init();
    for (int i = 1; i <= n; ++i)
        a[i].id = i, dp[i] = a[i].c, cnt[i] = 1; //,dp1[i] = a[i].c, cnt1[i] = 1;
    CDQ1(1, n);
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, dp[i]);
    cout << ans << endl;
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (dp[i] == ans) {
            sum += cnt[i];
            sum %= mod;
        }
    }
    cout << sum << endl;
    return 0;
}