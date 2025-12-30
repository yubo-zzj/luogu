#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 7;
struct func {
    int a, b, c;
    int p = 1;
    int sum(int x) {
        return a * x * x + b * x + c;
    }
} f[maxn];
void swap(func &a, func &b) {
    func c = a;
    a = b;
    b = c;
    return;
}
bool cmp(func a, func b) {
    return a.sum(1) < b.sum(1);
}
int n, m, cnt;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> f[i].a >> f[i].b >> f[i].c;
    return;
}
int main() {
    in();
    sort(f + 1, f + n + 1, cmp);
    while (cnt < m) {
        cnt++;
        cout << f[1].sum(f[1].p) << " ";
        f[1].p++;
        for (int i = 1; i <= n - 1 && f[i].sum(f[i].p) > f[i + 1].sum(f[i + 1].p); ++i) {
            swap(f[i], f[i + 1]);
        }
    }
    return 0;
}