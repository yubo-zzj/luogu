#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 7;
struct _mat_ {
    int x1, x2, y1, y2, id;
} a[maxn];
struct _edge_ {
    int x, y1, y2;
    bool is_lsft; 
}e[maxn << 1];
int cnt; 
int n;
int cur[maxn << 1], len;
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
        cur[++len] = a[i].y1;
        cur[++len] = a[i].y2;
        a[i].id = i;
    }
    sort(cur + 1, cur + len + 1);
    len = unique(cur + 1, cur + len + 1) - cur - 1;
    for (int i = 1; i <= n; ++i) {
        a[i].y1 = lower_bound(cur + 1, cur + len + 1, a[i].y1) - cur;
        a[i].y2 = lower_bound(cur + 1, cur + len + 1, a[i].y2) - cur;
    }
    for (int i = 1; i <= n; ++i) {
        e[++cnt] = {a[i].x1, a[i].y1, a[i].y2, 1};
        e[++cnt] = {a[i].x2, a[i].y1, a[i].y2, 0}; 
    }
    sort(e + 1, e + cnt + 1, [](const _edge_ &a, const _edge_ &b) { return a.x < b.x; });
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    
    return 0;
}