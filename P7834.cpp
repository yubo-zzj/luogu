#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
const int maxm = 5e5 + 7;
struct _G_ {
    int hd[maxn << 1], nxt[maxn << 1], to[maxn << 1], cnt;
    inline void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G;
struct _edge_ {
    int u, v, w;
} e[maxm];
struct _ji_ {
    int fa[maxn << 1];
    void init(int n) {
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
        return;
    }
    int getf(int x) {
        return x == fa[x] ? x : fa[x] = getf(fa[x]);
    }
} ji;
struct _kruskal_ {
    int wei[maxn << 1];
    int init(int n, int m) {
        int cnt = n;
        for (int i = 1; i <= m; ++i) {
            int u = ji.getf(e[i].u);
            int v = ji.getf(e[i].v);
            int w = e[i].w;
            if (u != v) {
                ji.fa[u] = ji.fa[v] = ++cnt;
                wei[cnt] = w;
                G.add(cnt, u);
                G.add(cnt, v);
            }
            if (cnt == 2 * n - 1)
                break;
        }
        return cnt;
    }
} rt;
struct _treecut_ {
    int size[maxn << 1], dep[maxn << 1], fa[maxn << 1][30], wei[maxn << 1];
    int dfn[maxn << 1], rank[maxn << 1], tot;
    void dfs(int u, int dp, int father) {
        // cout << u << " ";
        fa[u][0] = father;
        dep[u] = dp;
        size[u] = 1;
        dfn[++tot] = u;
        rank[u] = tot;
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            dfs(v, dp + 1, u);
            size[u] += size[v];
            wei[u] += wei[v];
        }
        return;
    }
} tc;
int val[maxn], cur[maxn];
struct _segtree_ {
    struct node {
        int data, ls, rs;
    };
    node sum[maxn << 6];
    int root[maxn << 1], cnt;
    int a[maxn << 1];
    void build(int &p, int l, int r) {
        if (!p)
            p = ++cnt;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(sum[p].ls, l, mid);
        build(sum[p].rs, mid + 1, r);
        return;
    }
    int update(int p, int l, int r, int pos) {
        int rt = ++cnt;
        sum[rt] = sum[p];
        sum[rt].data++;
        if (l < r) {
            int mid = (l + r) >> 1;
            if (pos <= mid)
                sum[rt].ls = update(sum[rt].ls, l, mid, pos);
            if (pos > mid)
                sum[rt].rs = update(sum[rt].rs, mid + 1, r, pos);
        }
        return rt;
    }
    int query(int nl, int nr, int l, int r, int k) {
        // cout << l << " " << r << endl;
        int s = sum[sum[nr].rs].data - sum[sum[nl].rs].data;
        // cout <<  sum[sum[nr].rs].data << endl;
        // cout << k << endl;
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (k > s)
            return query(sum[nl].ls, sum[nr].ls, l, mid, k - s);
        else
            return query(sum[nl].rs, sum[nr].rs, mid + 1, r, k);
    }
    void init(int n, int cnt) {
        for (int i = 1; i <= n; ++i) {
            if (tc.dfn[i] <= cnt)
                a[i] = val[tc.dfn[i]];
        }
        // for(int i = 1; i <= n; ++i) cout << a[i] << " ";
        build(root[0], 1, cnt);
        for (int i = 1; i <= n; ++i) {
            root[i] = root[i - 1];
            if (a[i])
                root[i] = update(root[i - 1], 1, cnt, a[i]);
        }
        return;
    }
} st;
int n, m, q, cnt;
void in() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        cur[i] = val[i];
    }
    sort(cur + 1, cur + n + 1);
    int len = unique(cur + 1, cur + n + 1) - cur - 1;
    for (int i = 1; i <= n; ++i) {
        val[i] = lower_bound(cur + 1, cur + len + 1, val[i]) - cur;
    }
    // for(int i = 1; i <= n; ++i) cout << val[i] << " ";
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    sort(e + 1, e + m + 1, [](const _edge_ &a, const _edge_ &b) { return a.w < b.w; });
    return;
}
void init() {
    in();
    ji.init(n << 1);
    cnt = rt.init(n, m);
    // cout << cnt << endl;
    for (int i = 1; i <= n; ++i)
        tc.wei[i] = 1;
    for (int i = 1; i <= cnt; ++i)
        if (ji.fa[i] == i)
            tc.dfs(i, 1, 0);
    st.init(cnt, n);
    for (int i = 1; i <= 23; ++i) {
        for (int j = 1; j <= cnt; ++j) {
            tc.fa[j][i] = tc.fa[tc.fa[j][i - 1]][i - 1];
        }
    }
    return;
}
int Find(int u, int limit) {
    for (int i = 23; i >= 0; --i) {
        if (rt.wei[tc.fa[u][i]] <= limit && tc.fa[u][i]) {
            u = tc.fa[u][i];
        }
    }
    return u;
}
int lstans;
int main() {
    init();
    // st.query(st.root[6], st.root[17], 1, n, 6);
    // for(int i = 1; i <= cnt; ++i) cout << st.a[i] << " ";
    while (q--) {
        int u, x, k;
        cin >> u >> x >> k;
        u = (u ^ lstans) % n + 1;
        k = (k ^ lstans) % n + 1;
        x = x ^ lstans;
        int ss = Find(u, x);
        // cout << u << " " << x << " " << k << " " << ss << '\n';
        // cout << tc.rank[ss] - 1 << " " << tc.rank[ss] + tc.size[ss] - 1 << endl << endl;
        if (tc.wei[ss] < k) {
            cout << -1 << '\n';
            lstans = 0;
        } else {
            lstans = st.query(st.root[tc.rank[ss] - 1], st.root[tc.rank[ss] + tc.size[ss] - 1], 1, n, k);
            lstans = cur[lstans];
            cout << lstans << '\n';
        }
    }
    // for(int i = 1; i <= cnt; ++i) cout << st.a[i] << " ";
    return 0;
}