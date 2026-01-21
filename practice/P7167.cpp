#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, q, d[maxn], c[maxn];
pair<int, int> st[maxn];
int tp;
int nxt[maxn][18];
long long sum[maxn][18];
int main() {
    ios_base ::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> d[i] >> c[i];
    }
    d[n + 1] = 1e9 + 7;
    for (int i = 1; i <= n + 1; ++i) {
        while (tp && d[i] > st[tp].first) {
            nxt[st[tp].second][0] = i;
            sum[st[tp].second][0] = c[st[tp].second];
            tp--;
        }
        st[++tp] = {d[i], i};
    }

    for (int i = 1; i <= 17; ++i) {
        for (int j = 1; j <= n; ++j) {
            nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
            sum[j][i] = sum[j][i - 1] + sum[nxt[j][i - 1]][i - 1];
        }
        // for (int k = 1; k <= n; ++k) {
        //     cout << sum[k][0] << ' ';
        // }
        // cout << endl; 
    }

    while (q--) {
        int r, v;
        cin >> r >> v;
        for (int i = 17; i >= 0; --i) {
            if (v > sum[r][i]) {
                v -= sum[r][i];
                r = nxt[r][i];
            }
            // cout << r << ' ';
        }
        cout << r << endl;
    }
    return 0;
}