#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
const int maxm = 3e5 + 7;
const int maxq = 5e5 + 7;
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
struct _query_ {
    int opt, v, time;
} q[maxq];
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
    int fa[maxn << 1][30], dep[maxn << 1], size[maxn << 1];
    int dfn[maxn << 1], rank[maxn << 1], tot;
    int a[maxn << 1];
    void dfs(int u, int dp, int father) {
        size[u] = 1;
        dfn[++tot] = u;
        rank[u] = tot;
        fa[u][0] = father;
        dep[u] = dp;
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            dfs(v, dp + 1, u);
            size[u] += size[v];
        }
        return;
    }
} tc;
struct _segtree_ {
    int sum[maxn << 3];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    inline void update(int p) {
        sum[p] = max(sum[ls(p)], sum[rs(p)]);
        return;
    }
    void build(int p, int l, int r) {
        if (l == r) {
            sum[p] = tc.a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);
        update(p);
        return;
    }
    int query(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return sum[p];
        }
        int res = -1;
        int mid = (l + r) >> 1;
        if (tl <= mid)
            res = max(res, query(ls(p), l, mid, tl, tr));
        if (tr > mid)
            res = max(res, query(rs(p), mid + 1, r, tl, tr));
        return res;
    }
    int ans;
    void del(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            if (sum[p] == ans) {
                int ll = l, rr = r;
                while (ll < rr) {
                    int mid = (ll + rr) >> 1;
                    if (sum[ls(p)] > sum[rs(p)])
                        rr = mid, p = ls(p);
                    else
                        ll = mid + 1, p = rs(p);
                }
                sum[p] = 0;
                int pp = p;
                while (pp) {
                    pp /= 2;
                    update(pp);
                }
            }
            return;
        }
        int mid = (l + r) >> 1;
        if (tl <= mid)
            del(ls(p), l, mid, tl, tr);
        if (tr > mid)
            del(rs(p), mid + 1, r, tl, tr);
        update(p);
        return;
    }
} st;
int Find(int x, int limit) {
    for (int i = 23; i >= 0; --i) {
        if (rt.wei[tc.fa[x][i]] <= limit && tc.fa[x][i])
            x = tc.fa[x][i];
    }
    return x;
}
int w[maxn];
int n, m, Q;
void in() {
    cin >> n >> m >> Q;
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    for (int i = 1; i <= m; ++i)
        cin >> e[i].u >> e[i].v;
    for (int i = 1; i <= Q; ++i)
        cin >> q[i].opt >> q[i].v;
    int time = 0;
    for (int i = Q; i >= 1; --i) {
        if (q[i].opt == 2) {
            time++;
            e[q[i].v].w = time;
        }
        q[i].time = time;
    }
    sort(e + 1, e + m + 1, [](const _edge_ &a, const _edge_ &b) { return a.w < b.w; });
    return;
}
void init() {
    in();
    ji.init(n << 1);
    int nn = n;
    n = rt.init(n, m);
    for (int i = 1; i <= n; ++i) {
        if (ji.fa[i] == i) {
            tc.dfs(i, 1, 0);
        }
    }
    // for(int i = 1; i <= n; ++i) cout << tc.fa[i][0] << " ";
    for (int i = 1; i <= 23; ++i) {
        for (int j = 1; j <= n; ++j) {
            tc.fa[j][i] = tc.fa[tc.fa[j][i - 1]][i - 1];
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (tc.dfn[i] <= nn)
            tc.a[i] = w[tc.dfn[i]];
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    st.build(1, 1, n);
    for (int i = 1; i <= Q; ++i) {
        if (q[i].opt == 1) {
            int s = Find(q[i].v, q[i].time);
            st.ans = st.query(1, 1, n, tc.rank[s], tc.rank[s] + tc.size[s] - 1);
            st.del(1, 1, n, tc.rank[s], tc.rank[s] + tc.size[s] - 1);
            cout << st.ans << '\n';
        }
    }
    return 0;
}