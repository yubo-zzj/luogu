#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
const int maxm = 4e5 + 7;
const int inf = 2e9 + 7;
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
    int u, v, l, a;
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
            int w = e[i].a;
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
int n, m;
int fa[maxn << 1][30];
int dis[maxn];
bool vis[maxn];
struct node {
    int u, val;
};
bool operator<(const node &a, const node &b) {
    return a.val > b.val;
}
int hd[maxn], nxt[maxm << 1], to[maxm << 1], wei[maxm << 1], cnt;
inline void add(int u, int v, int w) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    wei[cnt] = w;
    return;
}
priority_queue<node> q;
void dijstl() {
    for (int i = 1; i <= n; ++i)
        dis[i] = inf;
    memset(vis, 0, sizeof(vis));
    // while(!q.empty()) q.pop();
    dis[1] = 0;
    q.push((node){1, dis[1]});
    while (!q.empty()) {
        node x = q.top();
        q.pop();
        if (vis[x.u])
            continue;
        vis[x.u] = 1;
        for (int i = hd[x.u]; i; i = nxt[i]) {
            int v = to[i], w = wei[i];
            if (vis[v])
                continue;
            if (dis[v] > dis[x.u] + w) {
                dis[v] = dis[x.u] + w;
                q.push((node){v, dis[v]});
            }
        }
        // cout << 11 << endl;
    }
    // cout << 11 << endl;
    return;
}
int minss[maxn << 1], nn;
void dfs(int u, int father) {
    fa[u][0] = father;
    if (u <= nn)
        minss[u] = dis[u];
    else
        minss[u] = inf;
    for (int i = G.hd[u]; i; i = G.nxt[i]) {
        int v = G.to[i];
        if (v == father)
            continue;
        dfs(v, u);
        minss[u] = min(minss[u], minss[v]);
    }
    return;
}
void in() {
    cin >> n >> m;
    cnt = 0;
    G.cnt = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].l >> e[i].a;
        add(e[i].u, e[i].v, e[i].l);
        add(e[i].v, e[i].u, e[i].l);
    }
    sort(e + 1, e + m + 1, [](const _edge_ &a, const _edge_ &b) { return a.a > b.a; });
    return;
}
void init() {
    // cout << 1 << endl;
    in();
    // cout << 2 << endl;
    dijstl();
    // cout << 3 << endl;
    ji.init(n << 1);
    // cout << 4 << endl;
    nn = n;
    n = rt.init(n, m);
    // cout << 5 << endl;
    dfs(n, 0);
    // cout << 6 << endl;
    for (int i = 1; i <= 23; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    return;
}
int lstans;
int q1, k, s;
int v0, p0;
int work(int x) {
    for (int i = 23; i >= 0; --i) {
        if (rt.wei[fa[x][i]] > p0 && fa[x][i])
            x = fa[x][i];
    }
    return minss[x];
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        memset(fa, 0, sizeof(fa));
        memset(rt.wei, 0, sizeof(rt.wei));
        memset(e, 0, sizeof(e));
        memset(hd, 0, sizeof(hd));
        memset(nxt, 0, sizeof(nxt));
        memset(G.hd, 0, sizeof(G.hd));
        lstans = 0;
        init();
        cin >> q1 >> k >> s;
        while (q1--) {
            cin >> v0 >> p0;
            v0 = (v0 + k * lstans - 1) % nn + 1;
            p0 = (p0 + k * lstans) % (s + 1);
            lstans = work(v0);
            cout << lstans << '\n';
        }
    }
    return 0;
}