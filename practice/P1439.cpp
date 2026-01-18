#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int dp[maxn];
int n, a[maxn], b[maxn];
int pos[maxn];

struct node {
    int data, id;
} c[maxn], d[maxn];
bool cmp(node a, node b) {
    return a.data < b.data;
}
void work(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    work(l, mid);
    for (int i = l; i <= r; ++i) {
        d[i] = c[i];
    }
    sort(d + l + 0, d + mid + 1, cmp);
    sort(d + mid + 1, d + r + 1, cmp); 
    int p2 = mid + 1;
    int p1 = l;
    int t = 0;
    while (p2 <= r) {
        while (p1 <= mid && d[p1].data < d[p2].data) {
            t = max(t, dp[d[p1].id]);
            p1++;
        }
        dp[d[p2].id] = max(dp[d[p2].id], t + 1);
        p2++;
    }
    work(mid + 1, r);
    return;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        c[i].data = pos[b[i]];
        c[i].id = i;
    }
    for (int i = 1; i <= n; ++i)
        dp[i] = 1;
    work(1, n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}