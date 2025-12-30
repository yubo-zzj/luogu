#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e7 + 7;
const int maxn = 2e5 + 7;
// struct _AVL_ {
//     struct node {
//         int key, ls, rs, size, hight, count;
//     };
//     node a[maxn];
//     int cnt, root;
//     inline void up(int u) { // 维护
//         a[u].size = a[a[u].ls].size + a[a[u].rs].size + a[u].count;
//         a[u].hight = max(a[a[u].ls].hight, a[a[u].rs].hight) + 1;
//         return;
//     }
//     int left_rotate(int u) { // 左旋
//         int r = a[u].rs;
//         a[u].rs = a[r].ls;
//         a[r].ls = u;
//         up(u);
//         up(r);
//         return r;
//     }
//     int right_rotate(int u) { // 右旋
//         int l = a[u].ls;
//         a[u].ls = a[l].rs;
//         a[l].rs = u;
//         up(u);
//         up(l);
//         return l;
//     }
//     int maintain(int u) { // 检查u为根的子树，违规即旋转调整，返回调整后的头
//         int lh = a[a[u].ls].hight;
//         int rh = a[a[u].rs].hight;
//         if (lh - rh > 1) {
//             if (a[a[a[u].ls].ls].hight >= a[a[a[u].ls].rs].hight) {
//                 u = right_rotate(u);
//             } else {
//                 a[u].ls = left_rotate(a[u].ls);
//                 u = right_rotate(u);
//             }
//         } else if (rh - lh > 1) {
//             if (a[a[a[u].rs].rs].hight >= a[a[a[u].rs].ls].hight) {
//                 u = left_rotate(u);
//             } else {
//                 a[u].rs = right_rotate(a[u].rs);
//                 u = left_rotate(u);
//             }
//         }
//         return u;
//     }
//     int add(int u, int num) {
//         if (u == 0) {
//             cnt++;
//             a[cnt].key = num;
//             a[cnt].count = a[cnt].size = a[cnt].hight = 1;
//             return cnt;
//         }
//         if (a[u].key == num) {
//             a[u].count++;
//         } else if (a[u].key < num) {
//             a[u].rs = add(a[u].rs, num);
//         } else {
//             a[u].ls = add(a[u].ls, num);
//         }
//         up(u);
//         return maintain(u);
//     }
//     void add(int num) {
//         root = add(root, num);
//         return;
//     }
//     int small(int u, int num) {
//         if (u == 0) {
//             return 0;
//         }
//         if (a[u].key >= num) {
//             return small(a[u].ls, num);
//         } else {
//             return a[u].count + a[a[u].ls].size + small(a[u].rs, num);
//         }
//     }
//     int rank(int num) {
//         return small(root, num) + 1;
//     }
//     int remove_mostlft(int u, int mostlft) {
//         if (u == mostlft) {
//             return a[u].rs;
//         } else {
//             a[u].ls = remove_mostlft(a[u].ls, mostlft);
//             up(u);
//             return maintain(u);
//         }
//     }
//     int remove(int u, int num) {
//         if (a[u].key < num) {
//             a[u].rs = remove(a[u].rs, num);
//         } else if (a[u].key > num) {
//             a[u].ls = remove(a[u].ls, num);
//         } else {
//             if (a[u].count > 1) {
//                 a[u].count--;
//             } else {
//                 if (a[u].ls == 0 && a[u].rs == 0) {
//                     return 0;
//                 } else if (a[u].ls != 0 && a[u].rs == 0) {
//                     u = a[u].ls;
//                 } else if (a[u].rs != 0 && a[u].ls == 0) {
//                     u = a[u].rs;
//                 } else {
//                     int mostlft = a[u].rs;
//                     while (a[mostlft].ls) {
//                         mostlft = a[mostlft].ls;
//                     }
//                     a[u].rs = remove_mostlft(a[u].rs, mostlft);
//                     a[mostlft].ls = a[u].ls;
//                     a[mostlft].rs = a[u].rs;
//                     u = mostlft;
//                 }
//             }
//         }
//         up(u);
//         return maintain(u);
//     }
//     void remove(int num) {
//         if (rank(num) != rank(num + 1)) {
//             root = remove(root, num);
//         }
//         return;
//     }
//     int index(int u, int x) {
//         if (a[a[u].ls].size >= x) {
//             return index(a[u].ls, x);
//         } else if (a[a[u].ls].size + a[u].count < x) {
//             return index(a[u].rs, x - a[a[u].ls].size - a[u].count);
//         }
//         return a[u].key;
//     }
//     int index(int x) {
//         return index(root, x);
//     }
//     int pre(int u, int x) {
//         if (u == 0) {
//             return -inf;
//         }
//         if (a[u].key >= x) {
//             return pre(a[u].ls, x);
//         } else {
//             return max(a[u].key, pre(a[u].rs, x));
//         }
//     }
//     int pre(int x) {
//         return pre(root, x);
//     }
//     int nxt(int u, int x) {
//         if (u == 0) {
//             return inf;
//         }
//         if (a[u].key <= x) {
//             return nxt(a[u].rs, x);
//         } else {
//             return min(a[u].key, nxt(a[u].ls, x));
//         }
//     }
//     int nxt(int x) {
//         return nxt(root, x);
//     }
// } avl_tree;
struct _splay_ {
    struct node {
        int fa, key, ls, rs, count, size;
    };
    node a[maxn];
    int cnt, root;
    void up(int p) {
        a[p].size = a[a[p].ls].size + a[a[p].rs].size + 1;
        return;
    }
    bool which(int p) { // 0->left,1->right
        return a[a[p].fa].rs == p;
    }
    void rotate(int p) {
        int fa = a[p].fa, gf = a[fa].fa;
        bool sonf = which(p), song = which(fa);
        if (sonf) {
            a[fa].rs = a[p].ls;
            if (a[fa].rs) {
                a[a[fa].rs].fa = fa;
            }
            a[p].ls = fa;
        } else {
            a[fa].ls = a[p].rs;
            if (a[fa].ls) {
                a[a[fa].ls].fa = fa;
            }
            a[p].rs = fa;
        }
        if (gf != 0) {
            if (song) {
                a[gf].rs = p;
            } else {
                a[gf].ls = p;
            }
        }
        a[fa].fa = p;
        a[p].fa = gf;
        up(fa);
        up(p);
        return;
    }
    void splay(int p, int to) {
        int f = a[p].fa, g = a[f].fa;
        while (f != to) {
            if (g != to) {
                if (which(p) == which(f)) {
                    rotate(f);
                } else {
                    rotate(p);
                }
            }
            rotate(p);
            f = a[p].fa;
            g = a[f].fa;
        }
        if (!to) {
            root = p;
        }
        return;
    }
    int find(int rank) {
        int p = root;
        while (p) {
            if (a[a[p].ls].size + 1 == rank) {
                return p;
            } else if (a[a[p].ls].size >= rank) {
                p = a[p].ls;
            } else {
                rank -= a[a[p].ls].size + 1;
                p = a[p].rs;
            }
        }
        return 0;
    }
    void add(int num) {
        ++cnt;
        a[cnt].key = num;
        a[cnt].size = 1;
        if (!root) {
            root = cnt;
        } else {
            int f = 0, p = root, son = 0;
            while (p) {
                f = p;
                if (a[p].key <= num) {
                    son = 1;
                    p = a[p].rs;
                } else {
                    son = 0;
                    p = a[p].ls;
                }
            }
            if (son) {
                a[f].rs = cnt;
            } else {
                a[f].ls = cnt;
            }
            a[cnt].fa = f;
            splay(cnt, 0);
        }
        return;
    }
    int rank(int num) {
        int p = root, lst = root;
        int ans = 0;
        while (p) {
            lst = p;
            if (a[p].key >= num) {
                p = a[p].ls;
            } else {
                ans += a[a[p].ls].size + 1;
                p = a[p].rs;
            }
        }
        splay(lst, 0);
        return ans + 1;
    }
    void remove(int num) {
        int k = rank(num);
        if (k != rank(num + 1)) {
            int p = find(k);
            splay(p, 0);
            if (a[p].ls == 0) {
                root = a[p].rs;
            } else if (a[p].rs == 0) {
                root = a[p].ls;
            } else {
                int q = find(k + 1);
                splay(q, p);
                a[q].ls = a[p].ls;
                a[a[q].ls].fa = q;
                up(q);
                root = q;
            }
            a[root].fa = 0;
        }
        return;
    }
    int index(int x) {
        int p = find(x);
        splay(p, 0);
        return a[p].key;
    }
    int pre(int num) {
        int p = root, lst = root;
        int ans = -inf;
        while (p) {
            lst = p;
            if (a[p].key >= num) {
                p = a[p].ls;
            } else {
                ans = max(ans, a[p].key);
                p = a[p].rs;
            }
        }
        splay(lst, 0);
        return ans;
    }
    int nxt(int num) {
        int p = root, lst = root;
        int ans = inf;
        while (p) {
            lst = p;
            if (a[p].key <= num) {
                p = a[p].rs;
            } else {
                ans = min(ans, a[p].key);
                p = a[p].ls;
            }
        }
        splay(lst, 0);
        return ans;
    }
} a;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    while (n--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            a.add(x);
        } else if (opt == 2) {
            a.remove(x);
        } else if (opt == 3) {
            cout << a.rank(x) << '\n';
        } else if (opt == 4) {
            cout << a.index(x) << '\n';
        } else if (opt == 5) {
            cout << a.pre(x) << '\n';
        } else if (opt == 6) {
            cout << a.nxt(x) << '\n';
        }
    }
    return 0;
}