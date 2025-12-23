#include <bits/stdc++.h>
using namespace std;
const int maxn = 1007;
int n, m;
int a[maxn][maxn];
void in() {
    cin >> n >> m;
    return;
}
void add(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; ++i) {
        a[i][y1]++;
        a[i][y2 + 1]--;
    }
    return;
}
void out() {
    for (int i = 1; i <= n; ++i) {
        int s = 0;
        for (int j = 1; j <= n; ++j) {
            s += a[i][j];
            cout << s << " ";
        }
        cout << endl;
    }
    return;
}
int main() {
    in();
    for (int i = 1; i <= m; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        add(x1, y1, x2, y2);
    }
    out();
    return 0;
}