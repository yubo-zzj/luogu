#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7; 
int pos[maxn];
int l[maxn], r[maxn]; 
int hd; 
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        int p, opt;
        cin >> p >> opt; 
        if(opt == 1) {
            r[i] = r[p];
            l[r[p]] = i;
            r[p] = i;
            l[i] = p;
        } else {
            l[i] = l[p];
            r[l[p]] = i;
            l[p] = i;
            r[i] = p; 
        }
    }
    int hd = 1; 
    while(l[hd]) {
        hd = l[hd]; 
    }
    int m;
    cin >> m; 
    while(m--) {
        int x;
        cin >> x; 
        if(x == hd) {
            hd = r[x]; 
        } else {
            if(l[x] || r[x]) {
                r[l[x]] = r[x];
                l[r[x]] = l[x];
                l[x] = r[x] = 0;
            }
        }
    }
    for (int i = hd; i; i = r[i]) {
        cout << i << ' '; 
    }
        return 0;
}