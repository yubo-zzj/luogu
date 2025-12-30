#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e4 + 7;
int l[maxn], r[maxn];
int n, dpl[maxn], dpr[maxn];
int main() {
    ios_base ::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
    }
    dpl[1] = r[1] - 1 + r[1] - l[1];
    dpr[1] = r[1] - 1;
    for (int i = 2; i <= n; ++i) {
        dpl[i] = min(
            dpr[i - 1] + 1 + abs(r[i - 1] - r[i]) + r[i] - l[i], dpl[i - 1] + 1 + abs(l[i - 1] - r[i]) + r[i] - l[i]);
        dpr[i] = min(
            dpr[i - 1] + 1 + abs(r[i - 1] - l[i]) + r[i] - l[i], dpl[i - 1] + 1 + abs(l[i - 1] - l[i]) + r[i] - l[i]);
    }
    cout << min(n - l[n] + dpl[n], n - r[n] + dpr[n]) << endl;
    return 0;
}