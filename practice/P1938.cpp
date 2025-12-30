#include <bits/stdc++.h>
using namespace std;
int d, p, c, f, s, ans;
struct Edge {
    int tar, nxt, w;
} edge[575];
int tot, head[225];
void add(int u, int v, int w) {
    ++tot;
    edge[tot] = {v, head[u], w};
    head[u] = tot;
}
queue<int> q;
int wor[225], step;
bool in[225];
int search() {
    q.push(s);
    in[s] = 1;
    while (!q.empty()) {
        ++step;
        int u = q.front();
        q.pop();
        in[u] = 0;
        for (int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].tar;
            int w = edge[i].w;
            if (wor[v] > wor[u] + w) {
                wor[v] = wor[u] + w;
                ans = min(ans, wor[v]);
                // cout << "now ans = " << ans << endl;
                if (!in[v]) {
                    q.push(v);
                }
            }
        }
        if (step > p + f && !q.empty()) {
            return -1;
        }
    }
    return 100 - ans;
}
int main() {
    cin >> d >> p >> c >> f >> s;
    for (int i = 0; i < p; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v, -d);
    }
    for (int i = 0; i < f; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w - d);
    }
    int ans = search();
    cout << ans;
}