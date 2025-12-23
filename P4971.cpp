#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e6 + 7;
struct _pile_ {
    struct node {
        int ls, rs;
        ll data;
    };
    node a[maxn];
    int fa[maxn], dist[maxn];
    void init(int n, ll *p) {
        for (int i = 1; i <= n; ++i) {
            a[i].data = p[i];
            fa[i] = i;
            dist[i] = 0;
            a[i].ls = a[i].rs = 0;
        }
        dist[0] = -1;
        return;
    }
    int getf(int x) {
        return x == fa[x] ? x : fa[x] = getf(fa[x]);
    }
    int merge(int u, int v) {
        if (u == 0 || v == 0) {
            return u + v;
        }
        if (a[u].data < a[v].data) {
            swap(u, v);
        } else if (a[u].data == a[v].data && u > v) {
            swap(u, v);
        }
        a[u].rs = merge(a[u].rs, v);
        if (dist[a[u].rs] > dist[a[u].ls]) {
            swap(a[u].ls, a[u].rs);
        }
        dist[u] = dist[a[u].rs] + 1;
        fa[a[u].ls] = fa[a[u].rs] = u;
        return u;
    }
    void remove(int u) {
        int l = a[u].ls, r = a[u].rs;
        fa[l] = l, fa[r] = r;
        a[u].ls = a[u].rs = dist[u] = 0;
        merge(merge(l, r), getf(u));
        return; 
    }
} p;
int n, m;
ll a[maxn];
void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int t, w;
    ll k;
    cin >> t >> w >> k;
    while (t--) {
        init();
        p.init(n, a);
        while (m--) {
            int opt;
            cin >> opt;
            if (opt == 2) {
                int A;
                cin >> A;
                p.a[A].data = 0;
                p.remove(A); 
            }
            if (opt == 3) {
                int A;
                ll B;
                cin >> A >> B;
                int t1 = p.getf(A);
                if(p.a[t1].data <= B)
                    p.a[t1].data = 0; 
                else
                    p.a[t1].data -= B;
                p.remove(t1); 
            }
            if (opt == 4) {
                int A, B;
                cin >> A >> B;
                int t1 = p.getf(A);
                int t2 = p.getf(B);
                if (t1 != t2)
                    p.merge(t1, t2);
            }
        }
        ll ans = 0;
        ll maxx = 0;
        for (int i = 1; i <= n; ++i) {
            if (p.fa[i] == i) {
                // cout << i << endl;
                ans += p.a[i].data;
                // cout << i << " " << ans << endl;
                maxx = max(maxx, p.a[i].data);
            }
            // cout << p.a[i].data << " ";
        }
        if (w == 2)
            ans -= maxx;
        if (w == 3)
            ans += maxx;
        if (ans == 0) {
            cout << "Gensokyo ";
        } else if (ans <= k) {
            cout << "Heaven ";
        } else if (ans > k) {
            cout << "Hell ";
        }
        cout << ans << '\n';
    }
    return 0;
}