#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e2 + 7;
const int maxq = 6e4 + 7;
struct node {
    int data;
    int x, y;
} a[maxn * maxn];
struct _question_ {
    int x1, y1, x2, y2, k;
    int id;
} q[maxq];
int ans[maxq];
int n, m;
struct BIT {
    inline int lowbit(int pos) {
        return pos & -pos;
    }
    int c[maxn][maxn];
    void add(int x, int y, int v) {
        for (int i = x; i <= 500; i += lowbit(i)) {
            for (int j = y; j <= 500; j += lowbit(j)) {
                c[i][j] += v; 
            }
        }
        return; 
    }
    int sum(int x, int y) {
        int res = 0;
        for (int i = x; i; i  -= lowbit(i)) {
            for (int j = y; j; j -= lowbit(j)) {
                res += c[i][j]; 
            }
        }
        return res; 
    }
    int query(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1); 
    }
} bit;
struct _ST_ {
    vector<_question_> s[maxn * maxn * 4]; 
    void init() {
        for (int i = 1; i <= m; ++i) {
            s[1].push_back(q[i]); 
        }
        return; 
    }
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1; 
    }
    void work(int p, int l, int r) {
        if(l == r) {
            for(auto x : s[p]) {
                ans[x.id] = a[l].data; 
            }
            return; 
        }
        int mid = (l + r) >> 1;
        for (int i = l; i <= mid; ++i) {
            bit.add(a[i].x, a[i].y, 1); 
        }
        for(auto x : s[p]) {
            int ss = bit.query(x.x1, x.y1, x.x2, x.y2); 
            if(x.k > ss) {
                x.k -= ss;
                s[rs(p)].push_back(x); 
            } else{
                s[ls(p)].push_back(x); 
            }
        }
        s[p].clear();
        for (int i = l; i <= mid; ++i) {
            bit.add(a[i].x, a[i].y, -1); 
        }
        work(ls(p), l, mid);
        work(rs(p), mid + 1, r);
        return; 
    }
} st; 
void in() {
    cin >> n >> m;
    for (int i = 1, x; i <= n * n; ++i) {
        cin >> x;
        a[i] = {x, (i - 1) / n + 1, (i - 1) % n + 1};
    }
    sort(a + 1, a + n * n + 1, [](const node &a, const node &b) { return a.data < b.data; });
    for (int i = 1, a, b, c, d, k; i <= m; ++i) {
        cin >> a >> b >> c >> d >> k;
        q[i] = {a, b, c, d, k, i};
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    st.init();
    st.work(1, 1, n * n);
    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << '\n'; 
    }
        return 0;
}