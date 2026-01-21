#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9 + 7;
const int maxn = 5e5 + 7;
using ll = long long;
int c[maxn];
int lowbit(int p) {
    return p & -p;
}
void add(int pos, int x) {
    while (pos <= 5e5) {
        c[pos] += x;
        pos += lowbit(pos);
    }
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
int n, a[maxn];
ll ans;
void init() {
    cin >> n;
    int cur[maxn];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cur[i] = a[i]; 
    }
    sort(cur + 1, cur + n + 1);
    int len = unique(cur + 1, cur + n + 1) - cur - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(cur + 1, cur + len + 1, a[i]) - cur; 
    }
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    init();
    for (int i = n; i; --i) {
        ans += sum(a[i] - 1);
        add(a[i], 1); 
    }
    cout << ans << endl;
    return 0; 
}