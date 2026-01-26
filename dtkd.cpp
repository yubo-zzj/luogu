#include <bits/stdc++.h> 
using namespace std;
const int maxn = 1e5 + 7; 
using ull = unsigned long long; 
struct node {
    int ls, rs;
    ull data, tag; 
}a[maxn * 70];
int cnt;
void make(int &p, int l, int r) {
    p = ++cnt;
    a[p].data = (l + r) * 1ll * (r - l + 1) * 1ll / 2;
    return; 
}
void add(int &p, int l, int r, int tl, int tr, ull k) {
    if(p == 0) {
        make(p, l, r); 
    }
    if(l == r) {
        a[p].data += k; 
        return; 
    }
    push_down(p, l, r); 


    
} 


int main() {

    return 0; 
}