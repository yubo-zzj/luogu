#include <bits/stdc++.h> 
using namespace std;
const int maxs = 1e5;
const int maxn = 3e4 + 7;
int c[maxs + 1]; 
int lowbit(int pos) {
    return pos & -pos; 
}
void add(int pos, int x) {
    while(pos <= maxs) {
        c[pos] += x;
        pos += lowbit(pos); 
    }
    return; 
}
int query(int pos) {
    int res = 0; 
    while(pos) {
        res += c[pos];
        pos -= lowbit(pos); 
    }
    return res; 
}
int n, a[maxn];
int s1[maxn], s2[maxn]; 
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; 
    }
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    for (int i = 1; i <= n; ++i) {
        add(a[i], 1);
        s1[i] = query(a[i] - 1); 
    }
    memset(c, 0, sizeof(c));
    for (int i = n; i >= 1; --i) {
        add(maxs - a[i] + 1, 1);
        s2[i] = query(maxs - a[i]); 
    }
    long long ans = 0;
    for (int i = 2; i < n; ++i) {
        ans += s1[i] * s2[i]; 
    }
    cout << ans << endl; 
    return 0; 
}