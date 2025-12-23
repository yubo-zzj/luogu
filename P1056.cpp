#include <bits/stdc++.h>
using namespace std;
const int maxn = 1007;
struct node {
    int data, id;
};
bool cmp(node a, node b) {
    return a.data > b.data;
}
bool cmp1(node a, node b) {
    return a.id < b.id;
}
node a[maxn], b[maxn];
int m, n, k, l, d;
void in() {
    cin >> m >> n >> k >> l >> d;
    for (int i = 1; i <= m; ++i)
        a[i].id = i;
    for (int i = 1; i <= n; ++i)
        b[i].id = i;
    for (int i = 1; i <= d; ++i) {
        int x, y, p, q;
        cin >> x >> y >> p >> q;
        if (abs(x - p) == 1) {
            a[min(x, p)].data++;
        }
        if (abs(y - q) == 1) {
            b[min(y, q)].data++;
        }
    }
    return;
}
int main() {
    in();
    sort(a + 1, a + m + 1, cmp);
    sort(b + 1, b + n + 1, cmp);
    sort(a + 1, a + k + 1, cmp1);
    sort(b + 1, b + l + 1, cmp1);
    for (int i = 1; i <= k; ++i) {
        cout << a[i].id << " ";
    }
    cout << endl;
    for (int i = 1; i <= l; ++i) {
        cout << b[i].id << " ";
    }
    cout << endl;
    return 0;
}