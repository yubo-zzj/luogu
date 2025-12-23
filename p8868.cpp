#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int s = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
    return s;
}
using ull = unsigned long long;
const int maxn = 2.5e5 + 7;
int a[maxn], b[maxn];
struct _xdtree_ {
    ull suma[maxn << 2], sumb[maxn << 2];
    ull maxa[maxn << 2], maxb[maxn << 2];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    inline void update(int p) {
        suma[p] = suma[ls(p)] + suma[rs(p)];
        sumb[p] = sumb[ls(p)] + sumb[rs(p)];
        maxa[p] = max(maxa[ls(p)], maxa[rs(p)]);
        maxb[p] = max(maxb[ls(p)], maxb[rs(p)]);
        return;
    }
    void build(int p, int l, int r) {
        if (l == r) {
            suma[p] = a[l], sumb[p] = b[l];
            maxa[p] = a[l], maxb[p] = b[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);
        update(p);
        return;
    }

} xdtree;
int T, n;

void in() {
    T = read(), n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= n; ++i)
        b[i] = read();
    return;
}
int main() {
    in();
    xdtree.build(1, 1, n);

    return 0;
}