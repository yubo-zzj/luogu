#include <bits/stdc++.h>
using namespace std; 
int lowbit(int p) {
    return p & -p;
}
const int maxn = 5e5 + 7;
int c[maxn];
void add(int pos, int x) {
    while (pos <= 5e5) {
        c[pos] += x;
        pos += lowbit(pos);
    }
    return;
}
void add(int l, int r, int x) {
    add(l, x);
    add(r + 1, -x);
    return;
}
int sum(int pos) {
    int res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
int query(int l, int r) {
    return sum(r) - sum(l - 1);
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        add(i, i, x);
    }
    while (m--) {
        int opt, x, y, k;
        cin >> opt;
        if (opt == 1) {
            cin >> x >> y >> k;
            add(x, y, k);
        } else {
            cin >> x;
            cout << sum(x) << endl;
        }
    }
    return 0;
}