#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e4 + 7;
int n;
int l[maxn], r[maxn];
int dpl[maxn], dpr[maxn];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
    }
    dpl[1] = r[1] - 1 + r[1] - l[1];
    dpr[1] = r[1] - 1;
    for (int i = 2; i <= n; ++i) {
        dpl[i] = min(
            dpl[i - 1] + abs(r[i] - l[i - 1]) + r[i] - l[i] + 1, dpr[i - 1] + abs(r[i] - r[i - 1]) + r[i] - l[i] + 1);
        dpr[i] = min(
            dpl[i - 1] + abs(l[i] - l[i - 1]) + r[i] - l[i] + 1, dpr[i - 1] + abs(l[i] - r[i - 1]) + r[i] - l[i] + 1);
    }
    cout << min(dpl[n] + n - l[n], dpr[n] + n - r[n]) << endl;
    return 0;
}