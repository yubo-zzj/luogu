#include <bits/stdc++.h> 
using namespace std;
const int maxn = 3e2 + 7;
const int maxc = 1e2 + 7; 
int c[maxn][maxn][maxc];
int a[maxn][maxn]; 
int lowbit(int pos) {
    return pos & -pos; 
}
void add(int x, int y, int sum, int w) {
    for (int i = x; i <= 3e2; i += lowbit(i)) {
        for (int j = y; j <= 3e2; j += lowbit(j)){
            c[i][j][sum] += w; 
        }
    }
    return; 
}
int sum(int x, int y, int s) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        for (int j = y; j; j -= lowbit(j)) {
            res += c[i][j][s]; 
        }
    }
    return res; 
}
int query(int x_1, int y_1, int x_2, int y_2, int s) {
    return sum(x_2, y_2, s) + sum(x_1 - 1, y_1 - 1, s) - sum(x_1 - 1, y_2, s) - sum(x_2, y_1 - 1, s); 
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            add(i, j, a[i][j], 1); 
        }
    }
    int q;
    cin >> q; 
    while(q--) {
        int opt;
        cin >> opt; 
        if(opt == 1) {
            int x, y, s;
            cin >> x >> y >> s;
            add(x, y, a[x][y], -1);
            add(x, y, s, 1);
            a[x][y] = s; 
        }
        if(opt == 2) {
            int x_1, x_2, y_1, y_2, s;
            cin >> x_1 >> x_2 >> y_1 >> y_2 >> s;
            cout << query(x_1, y_1, x_2, y_2, s) << '\n';
        }
    }
    return 0; 
}