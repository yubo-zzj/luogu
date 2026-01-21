#include <bits/stdc++.h>
using namespace std; 
int lowbit(int p) {
    return p & -p; 
}
const int maxn = 5e5 + 7; 
int c[maxn]; 
void add(int pos, int x) {
    while(pos <= 5e5) {
        c[pos] += x;
        pos += lowbit(pos); 
    }
    return; 
}
int sum(int pos) {
    int res = 0; 
    while(pos) {
        res += c[pos];
        pos -= lowbit(pos); 
    }
    return res; 
}
int query(int l, int r) {
    return sum(r) - sum(l - 1); 
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        add(i, x); 
    }
    while(m--) {
        int opt, x, y;
        cin >> opt >> x >> y; 
        if(opt == 1) {
            add(x, y); 
        } 
        else
            cout << query(x, y) << endl; 

    }
    return 0; 

}