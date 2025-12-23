#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 7;
struct _treearry_ {
    struct node {
        int data;
        double time;
    } c[maxn];
    int lowbit(int x) {
        return x & -x;
    }
    void more(int pos, int x, double time) {
        while (pos <= 5e4) {
            if (c[pos].data < x)
                c[pos] = (node){x, time};
            else if (c[pos].data == x)
                c[pos].time += time;
            pos += lowbit(pos);
        }
        return;
    }
    node query(int pos) {
        node x = (node){0, 0.0};
        while (pos) {
            if (c[pos].data == x.data)
                x.time += c[pos].time;
            if (c[pos].data > x.data)
                x = c[pos];
            pos -= lowbit(pos);
        }
        return x;
    }
    void clear(int pos) {
        node x = (node){0, 0.0};
        while (pos <= 5e4) {
            c[pos] = x;
            pos += lowbit(pos);
        }
        return;
    }
} treearry;
struct node {
    int h, v, id;
} a[maxn], b[maxn];
bool cmp(node a, node b) {
    return a.h > b.h;
}
int dp1[maxn], dp2[maxn];
double cnt1[maxn], cnt2[maxn];
int lenh, lenv;
// dp1[i] ->以i结尾 最长长度
// cnt1[i]->以i结尾 最长长度的个数
// dp2[i] ->以i开头 最长长度  //reverse同法求
// cnt2[i]->以i开头 最长长度的个数
void CDQ1(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ1(l, mid);
    for (int i = l; i <= r; ++i)
        b[i] = a[i];
    sort(b + l + 0, b + mid + 1, cmp);
    sort(b + mid + 1, b + r + 1, cmp);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && b[p1].h >= b[p2].h) {
            treearry.more(lenv - b[p1].v + 1, dp1[b[p1].id], cnt1[b[p1].id]);
            p1++;
        }
        int v;
        double t;
        v = treearry.query(lenv - b[p2].v + 1).data;
        t = treearry.query(lenv - b[p2].v + 1).time;
        if (v + 1 > dp1[b[p2].id]) {
            dp1[b[p2].id] = v + 1;
            cnt1[b[p2].id] = t;
        } else if (v + 1 == dp1[b[p2].id]) {
            cnt1[b[p2].id] += t;
        }
        p2++;
    }
    for (int i = l; i < p1; ++i) {
        treearry.clear(lenv - b[i].v + 1);
    }
    CDQ1(mid + 1, r);
    return;
}
bool cmp1(node a, node b) {
    return a.h < b.h;
}
void CDQ2(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ2(l, mid);
    for (int i = l; i <= r; ++i)
        b[i] = a[i];
    sort(b + l + 0, b + mid + 1, cmp1);
    sort(b + mid + 1, b + r + 1, cmp1);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && b[p1].h <= b[p2].h) {
            treearry.more(b[p1].v, dp2[b[p1].id], cnt2[b[p1].id]);
            p1++;
        }
        int v;
        double t;
        v = treearry.query(b[p2].v).data;
        t = treearry.query(b[p2].v).time;
        if (v + 1 > dp2[b[p2].id]) {
            dp2[b[p2].id] = v + 1;
            cnt2[b[p2].id] = t;
        } else if (v + 1 == dp2[b[p2].id]) {
            cnt2[b[p2].id] += t;
        }
        p2++;
    }
    for (int i = l; i < p1; ++i) {
        treearry.clear(b[i].v);
    }
    CDQ2(mid + 1, r);
    return;
}
int n;
void in() {
    cin >> n;
    int cur1[maxn], cur2[maxn];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].h >> a[i].v;
        a[i].id = i;
        // cur1[i] = a[i].h;
        cur2[i] = a[i].v;
    }
    // sort(cur1 + 1, cur1 + n + 1);
    sort(cur2 + 1, cur2 + n + 1);
    // lenh = unique(cur1 + 1, cur1 + n + 1) - cur1 - 1;
    lenv = unique(cur2 + 1, cur2 + n + 1) - cur2 - 1;
    for (int i = 1; i <= n; ++i) {
        // a[i].h = lower_bound(cur1 + 1, cur1 + lenh + 1, a[i].h) - cur1;
        a[i].v = lower_bound(cur2 + 1, cur2 + lenv + 1, a[i].v) - cur2;
    }
    for (int i = 1; i <= n; ++i) {
        dp1[i] = dp2[i] = 1;
        cnt1[i] = cnt2[i] = 1.0;
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    CDQ1(1, n);
    int p1 = 1, p2 = n;
    while (p1 < p2) {
        swap(a[p1].h, a[p2].h);
        swap(a[p1].v, a[p2].v);
        p1++;
        p2--;
    }
    memset(treearry.c, 0, sizeof(treearry.c));
    CDQ2(1, n);
    p1 = 1, p2 = n;
    while (p1 < p2) {
        swap(dp2[p1], dp2[p2]);
        swap(cnt2[p1], cnt2[p2]);
        p1++;
        p2--;
    }
    // for(int i = 1; i <= n; ++i) cout << dp1[i] << " "; cout << endl;
    // for(int i = 1; i <= n; ++i) cout << dp2[i] << " "; cout << endl;
    int maxlen = 0;
    for (int i = 1; i <= n; ++i) {
        maxlen = max(maxlen, dp1[i]);
    }
    double cnt = 0.0;
    for (int i = 1; i <= n; ++i) {
        if (dp1[i] == maxlen)
            cnt += cnt1[i];
    }
    cout << maxlen << endl;
    for (int i = 1; i <= n; ++i) {
        if (dp1[i] + dp2[i] - 1 == maxlen)
            cout << cnt1[i] * cnt2[i] / cnt << " ";
        else
            cout << "0.00000 ";
        // cout << endl;
    }
    return 0;
}