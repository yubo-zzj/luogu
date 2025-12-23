#include <bits/stdc++.h>
using namespace std;
const int maxn = 17;
int n;
int t[maxn], d[maxn], l[maxn], e[maxn];
bool flg = 0;
bool bk[maxn]; 
void dfs(int num, int time) {
    if (flg)
        return; 
    if(num == n) {
        flg = 1;
        return; 
    }
    // for (int i = 1; i <= n; ++i) {
    //     if(e[i] < time)
    //         return; 
    // }
    for (int i = 1; i <= n; ++i) {
        if(bk[i])
            continue;  
        if(time <= e[i]) {
            bk[i] = 1;
            dfs(num + 1, max(time + l[i], t[i] + l[i]));
            bk[i] = 0; 
        }
    }
    return; 
}
int mint = 1e9 + 7; 
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> d[i] >> l[i];
        mint = min(mint, t[i]);
        e[i] = t[i] + d[i];
    }
    return;
}
void init() {
    memset(t, 0, sizeof(t));
    memset(d, 0, sizeof(d));
    memset(l, 0, sizeof(l));
    memset(e, 0, sizeof(e));
    memset(bk, 0, sizeof(bk)); 
    flg = 0; 
    return;
}
int main() {
    int q;
    cin >> q;
    while (q--) {
        init();
        in();
        dfs(0, 0); 
        if(flg)
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n'; 
    }
    return 0;
}