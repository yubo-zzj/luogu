#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
const int maxs = (1 << 20) + 7; 
int n, m, x;
int a[maxn];
int pos[maxs];
int st[maxn][18];
int lg[maxn]; 
int query(int l, int r) {
    return max(st[l][lg[r - l + 1]], st[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]); 
}
int main() {
    cin >> n >> m >> x;
    lg[0] = -1; 
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
        st[i][0] = pos[a[i] ^ x]; 
        lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= lg[n]; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]); 
        }
    }
    // for (int i = 0; i <= lg[n]; ++i) {
    //     for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
    //         cout << st[j][i] << " "; 
    //     }
    //     cout << endl; 
    // }
    while(m--) {
        int l, r;
        cin >> l >> r;
        // cout << query(l, r) << endl; 
        if(query(l, r) >= l) {
            cout << "yes" << '\n'; 
        }else
            cout << "no" << '\n'; 
    }
    return 0; 
}