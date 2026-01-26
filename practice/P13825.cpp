#include <bits/stdc++.h> 
using namespace std;
const int maxn = 1e5 + 7;
struct node {
    __int128 tag = 0, data = 0;
    int l, r; 
} s[maxn << 6];
int cnt; 
int n, m;
int root; 
void update(int p, int l, int r) {
    int mid = (l + r) >> 1; 
    if(!s[p].l) {
        s[p].l = ++cnt;
        s[s[p].l].data = (l + mid) * 1ll * (mid - l + 1) * 1ll / 2; 
    }
    if(!s[p].r) {
        s[p].r = ++cnt;
        s[s[p].r].data = (mid + 1 + r) * 1ll * (r - mid) * 1ll / 2; 
    }
    s[p].data = s[s[p].l].data + s[s[p].r].data;
    return; 
}
void fun(int &p, int l, int r, __int128 k) {
    if(!p) {
        p = ++cnt;
        s[p].data = (l + r) * 1ll * (r - l + 1) * 1ll / 2; 
    }
    s[p].data += k*(r - l + 1);
    s[p].tag += k;
    return; 
}
void push_down(int p, int l, int r) {
    if(!s[p].tag)
        return;
    int mid = (l + r) >> 1;
    fun(s[p].l, l, mid, s[p].tag);
    fun(s[p].r, mid + 1, r, s[p].tag);
    s[p].tag = 0;
    return; 
}
void add(int &p, int l, int r, int tl, int tr, __int128 k) {
    if(!p) {
        p = ++cnt;
        s[p].data = (l + r) * 1ll * (r - l + 1) * 1ll / 2;
    }
    if(l >= tl && r <= tr) {
        s[p].data += k * (r - l + 1);
        s[p].tag += k;
        return; 
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1; 
    if(tl <= mid)
        add(s[p].l, l, mid, tl, tr, k); 
    if(tr >  mid)
        add(s[p].r, mid + 1, r, tl, tr, k);
    update(p, l, r); 
    return; 
}
__int128 query(int &p, int l, int r, int tl, int tr) {
    if(!p) {
        p = ++cnt;
        s[p].data = (l + r) * 1ll * (r - l + 1) * 1ll / 2; 
    }
    if(l >= tl && r <= tr) {
        return s[p].data; 
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    __int128 res = 0; 
    if(tl <= mid)
        res += query(s[p].l, l, mid, tl, tr); 
    if(tr >  mid)
        res += query(s[p].r, mid + 1, r, tl, tr);
    update(p, l, r); 
    return res; 
}
void write(__int128 n) {
    if(n >= 10) {
        write(n / 10); 
    }
    putchar(n % 10 + '0');
    return; 
}
int main() {
    cin >> n >> m;
    // __int128 x = 100123123000001010;
    while(m--) {
        int opt, l, r;
        long long kk; 
        __int128 k;
        cin >> opt; 
        if(opt == 1) {
            cin >> l >> r >> kk;
            k = kk; 
            add(root, 1, n, l, r, k); 
        } 
        if(opt == 2) {
            cin >> l >> r;
            write(query(root, 1, n, l, r));
            putchar('\n'); 
        }
    }
    return 0; 
}