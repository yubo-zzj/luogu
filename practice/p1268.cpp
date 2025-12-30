#include <bits/stdc++.h>
using namespace std;
const int maxn = 37;
int n, a[maxn][maxn];
long long ans = 0;
void in() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    }
    return;
}
int main() {
    in();

    return 0;
}