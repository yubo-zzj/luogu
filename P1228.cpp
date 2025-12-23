#include <bits/stdc++.h>
using namespace std;
struct node {
    int x, y;
};
struct block {
    node x, y;
};
void out(block a, int opt) {
    if (opt == 1) {
        cout << a.y.x << " " << a.y.y << " " << opt << endl;
        return;
    }
    if (opt == 2) {
        cout << a.y.x << " " << a.x.y << " " << opt << endl;
        return;
    }
    if (opt == 3) {
        cout << a.x.x << " " << a.y.y << " " << opt << endl;
        return;
    }
    if (opt == 4) {
        cout << a.x.x << " " << a.x.y << " " << opt << endl;
        return;
    }
    return;
}
block son(block a, int opt) {
    block b;
    if (opt == 1) {
        b.x = a.x;
        b.y.x = (a.x.x + a.y.x - 1) / 2;
        b.y.y = (a.x.y + a.y.y - 1) / 2;
        return b;
    }
    if (opt == 2) {
        b.x.x = a.x.x;
        b.x.y = (a.x.y + a.y.y + 1) / 2;
        b.y.x = (a.x.x + a.y.x - 1) / 2;
        b.y.y = a.y.y;
        return b;
    }
    if (opt == 3) {
        b.x.y = a.x.y;
        b.x.x = (a.x.x + a.y.x + 1) / 2;
        b.y.x = a.y.x;
        b.y.y = (a.x.y + a.y.y - 1) / 2;
        return b;
    }
    if (opt == 4) {
        b.y = a.y;
        b.x.x = (a.x.x + a.y.x + 1) / 2;
        b.x.y = (a.x.y + a.y.y + 1) / 2;
        return b;
    }
    if (opt == 5) {
        int t = (a.y.y - a.x.y + 1) / 4;
        b.x.x = a.x.x + t;
        b.x.y = a.x.y + t;
        b.y.x = a.y.x - t;
        b.y.y = a.y.y - t;
        return b;
    }
    return b;
}
void out(block a, int opt, int k) {
    if (k == 1) {
        out(a, opt);
        return;
    }
    if (opt == 1) {
        out(son(a, 5), 1, k - 1);
        out(son(a, 2), 3, k - 1);
        out(son(a, 3), 2, k - 1);
        out(son(a, 4), 1, k - 1);
        return;
    }
    if (opt == 2) {
        out(son(a, 5), 2, k - 1);
        out(son(a, 3), 2, k - 1);
        out(son(a, 1), 4, k - 1);
        out(son(a, 4), 1, k - 1);
        return;
    }
    if (opt == 3) {
        out(son(a, 5), 3, k - 1);
        out(son(a, 2), 3, k - 1);
        out(son(a, 1), 4, k - 1);
        out(son(a, 4), 1, k - 1);
        return;
    }
    if (opt == 4) {
        out(son(a, 5), 4, k - 1);
        out(son(a, 1), 4, k - 1);
        out(son(a, 2), 3, k - 1);
        out(son(a, 3), 2, k - 1);
        return;
    }
    return;
}
int dis(block a, int x, int y) {
    int kx = (a.x.x + a.y.x - 1) / 2;
    int ky = (a.x.y + a.y.y - 1) / 2;
    if (x <= kx && y <= ky)
        return 1;
    if (x > kx && y <= ky)
        return 3;
    if (x > kx && y > ky)
        return 4;
    if (x <= ky && y > ky)
        return 2;
    return 0;
}
void work(block now, int k, int x, int y) {
    if (!k)
        return;
    out(now, dis(now, x, y), k);
    work(son(now, dis(now, x, y)), k - 1, x, y);
    return;
}
int k, x, y;
int main() {
    cin >> k >> x >> y;
    block now;
    now.x.x = now.x.y = 1;
    now.y.x = now.y.y = (1 << k);
    work(now, k, x, y);
    return 0;
}