#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 7;
const int maxs = 1e6 + 7;
struct node {
    int data, id;
} a[maxn], b[maxn];
bool cmp(node a, node b) {
    return a.data < b.data;
}
int dp[maxn];
void CDQ(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    for (int i = l; i <= r; ++i)
        b[i] = a[i];
    sort(b + l + 0, b + mid + 1, cmp);
    sort(b + mid + 1, b + r + 1, cmp);
    int p1 = l, p2 = mid + 1;
    int maxans = 0;
    while (p2 <= r) {
        while (p1 <= mid && b[p1].data < b[p2].data) {
            maxans = max(maxans, dp[b[p1].id]);
            p1++;
        }
        dp[b[p2].id] = max(dp[b[p2].id], maxans + 1);
        p2++;
    }
    CDQ(mid + 1, r);
    return;
}
int n;
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].data;
        dp[i] = 1;
        a[i].id = i;
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    CDQ(1, n);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, dp[i]);
    cout << ans << endl;
    return 0;
}