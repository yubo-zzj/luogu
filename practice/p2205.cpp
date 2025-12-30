#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, k;
int a[maxn];
int cur[maxn];
int b[maxn];
void add(int l, int r) {
    b[l]++;
    b[r + 1]--;
    return;
}
int len;
void LSH() {
    sort(cur, cur + n + 1);
    len = unique(cur, cur + n + 1) - cur - 1;
    for (int i = 0; i <= n; ++i) {
        a[i] = lower_bound(cur, cur + len + 1, a[i]) - cur;
    }
    return;
}
void in() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        int x;
        char ch;
        cin >> x >> ch;
        if (ch == 'R')
            a[i] = a[i - 1] + x;
        if (ch == 'L')
            a[i] = a[i - 1] - x;
        cur[i] = a[i];
    }
    return;
}
int main() {
    in();
    LSH();
    for (int i = 1; i <= n; ++i) {
        int l = a[i - 1];
        int r = a[i];
        if (l > r)
            swap(l, r);
        add(l + 1, r);
    }
    long long ans = 0;
    int sum = 0;
    for (int i = 0; i <= len; ++i) {
        sum += b[i];
        if (sum >= k) {
            ans += cur[i] - cur[i - 1];
        }
    }
    cout << ans << endl;
    return 0;
}