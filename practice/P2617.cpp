#include <bits/stdc++.h> 
using namespace std;
const int maxn = 1e5 + 7;
struct _question_ {
    int l, r, k;
    char type; 
} q[maxn]; 
struct node {
    int data, id;
} a[maxn]; 
struct _ST_ {
    vector<_question_> s[maxn << 3]; 
    inline int ls(int p) {
        return p << 1; 
    }
    inline int rs(int p) {
        return p << 1 | 1; 
    }
    
} st; 
int n, m,cur[maxn << 1], len; 
void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].data;
        a[i].id = i; 
        cur[++len] = a[i].data; 
    }
    for (int i = 1; i <= m; ++i) {
        cin >> q[i].type; 
        if(q[i].type == 'C') {
            cin >> q[i].l >> q[i].k;
            cur[++len] = q[i].k; 
        } else {
            cin >> q[i].l >> q[i].r >> q[i].k; 
        }
    }
    sort(cur + 1, cur + len + 1);
    len = unique(cur + 1, cur + len + 1) - cur - 1;
    for (int i = 1; i <= n; ++i) {
        a[i].data = lower_bound(cur + 1, cur + len + 1, a[i].data) - cur; 
    }
    for (int i = 1; i <= m; ++i) {
        if(q[i].type == 'C') {
            q[i].k = lower_bound(cur + 1, cur + len + 1, q[i].k) - cur; 
        }
    }
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();

    return 0;
}