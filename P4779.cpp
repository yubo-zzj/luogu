#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9 + 7;
const int maxn = 1e5 + 7;
struct node {
    int val, id;
};
bool operator < (const node&a, const node&b) {
    return a.val > b.val; 
}
struct edge {
    int v, w;
};
priority_queue<node> q;
vector<edge> V[maxn];
bool vis[maxn];
int dis[maxn];
int n, m, s;
void dijk() {
    for (int i = 1; i <= n; ++i)
        dis[i] = inf;
    dis[s] = 0;
    q.push(node{dis[s], s});
    while (!q.empty()) {
        auto x = q.top();
        q.pop();
        if (vis[x.id])
            continue;
        vis[x.id] = 1;
        for (auto i : V[x.id]) {
            if (dis[i.v] > dis[x.id] + i.w) {
                dis[i.v] = dis[x.id] + i.w;
                if(!vis[i.v]) q.push(node{dis[i.v], i.v});
            }
        }
    }
    return;
}
void in() {
    cin >> n >> m >> s;
    for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w;
        V[u].push_back(edge{v, w});
    }
    return;
}
int main() {
    in();
    dijk();
    for (int i = 1; i <= n; ++i) {
        cout << dis[i] << " ";
    }
    return 0;
}