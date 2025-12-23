#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 3e5 + 7;
struct _pile_ {
    struct _city_ {    // 城池
        ll h, f, a, v; // h->防御，f->被f号节点管辖，(a, v)->参数
    } a[maxn];
    struct _human_ {
        ll s, c; // s->战斗力，c->第一个打的城
    } b[maxn];
    struct node {
        ll data, tag_add, tag_mul;
        int ls, rs;
        int id;
    } p[maxn];
    int dist[maxn];
    // int fa[maxn];
    int dp[maxn];
    int pre_dp[maxn];
    int rt[maxn];
    // int getf(int x) {
    //     return x == fa[x] ? x : fa[x] = getf(fa[x]);
    // }

    void update(int u, int v) {
        p[v].tag_add *= p[u].tag_mul;
        p[v].tag_add += p[u].tag_add;
        p[v].tag_mul *= p[u].tag_mul;
        p[v].data *= p[u].tag_mul;
        p[v].data += p[u].tag_add;
        return;
    }
    void push_down(int u) {
        if (p[u].tag_add == 0 && p[u].tag_mul == 1)
            return;
        int l = p[u].ls;
        int r = p[u].rs;
        if (l)
            update(u, l);
        if (r)
            update(u, r);
        p[u].tag_add = 0;
        p[u].tag_mul = 1;
        return;
    }
    int merge(int u, int v) {
        if (u == 0 || v == 0)
            return u + v;
        push_down(u);
        push_down(v);
        if (p[u].data > p[v].data)
            swap(u, v);
        p[u].rs = merge(p[u].rs, v);
        int l = p[u].ls;
        int r = p[u].rs;
        if (dist[r] > dist[l]) {
            swap(p[u].ls, p[u].rs);
        }
        dist[u] = dist[p[u].rs] + 1;
        // fa[p[u].rs] = fa[p[u].ls] = u;
        return u;
    }
    // ll top(int u) {
    //     // u = getf(u);
    //     return p[u].data;
    // }
    // void pop(int &u) {
    //     // u = getf(u);
    //     push_down(u);
    //     int l = p[u].ls;
    //     int r = p[u].rs;
    //     // fa[l] = l, fa[r] = r;
    //     p[u].ls = p[u].rs = 0;
    //     if (!p[u].ls)
    //         u = -1;
    //     else
    //         u = merge(l, r);
    //     // fa[u] = s;
    //     return;
    // }
    void change(int u, int opt, ll v) {
        // u = getf(u);
        if (opt == 0) {
            p[u].tag_add += v;
            p[u].data += v;
            return;
        } else {
            p[u].tag_add *= v;
            p[u].tag_mul *= v;
            p[u].data *= v;
            return;
        }
        return;
    }
    void in(int &n, int &m) {
        cin >> n >> m;
        dist[0] = -1;
        dp[1] = 1;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].h;
            rt[i] = -1;
        }
        // for (int i = 1; i <= n; ++i)
        //     cout << a[i].h << " ";
        for (int i = 2; i <= n; ++i) {
            cin >> a[i].f >> a[i].a >> a[i].v;
            dp[i] = dp[a[i].f] + 1;
        }
        for (int i = 1; i <= m; ++i) {
            cin >> b[i].s >> b[i].c;
            // pre_dp[i] = dp[b[i].c];
            p[i].data = b[i].s;
            p[i].tag_mul = 1ll;
            // fa[i] = i;
            // p[i].id = i;
            if (rt[b[i].c] == -1)
                rt[b[i].c] = i;
            else
                rt[b[i].c] = merge(rt[b[i].c], i);
        }
        return;
    }
} p;
int n, m;
// vector<int> v[maxn];
int ans[maxn];
int ot[maxn];
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    p.in(n, m);
    for (int i = n; i >= 1; --i) {
        while (p.rt[i] != -1) {
            if (p.p[p.rt[i]].data < p.a[i].h) {
                ot[p.rt[i]] = i;
                // ans[i]++;
                p.push_down(p.rt[i]);
				if(!p.p[p.rt[i]].ls) p.rt[i]=-1;
				else p.rt[i]=p.merge(p.p[p.rt[i]].ls,p.p[p.rt[i]].rs);
            } else
                break;
        }
        if (i == 1)
            break;
        if (p.rt[i] == -1)
            continue;
        p.change(p.rt[i], p.a[i].a, p.a[i].v);
        p.push_down(p.rt[i]);
        if (p.rt[p.a[i].f] == -1)
            p.rt[p.a[i].f] = p.rt[i];
        else
            p.rt[p.a[i].f] = p.merge(p.rt[p.a[i].f], p.rt[i]);
    }

    for (int i = 1; i <= m; ++i) {
        ans[ot[i]]++;
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }
    for (int i = 1; i <= m; ++i) {
        cout << p.dp[p.b[i].c] - p.dp[ot[i]] << '\n';
    }
    return 0;
}