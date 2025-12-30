#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e9 + 7;
const int maxn = 1e5 + 7;
struct _AVL_ {
    struct node {
        int key, ls, rs, size, hight, count;
    };
    node a[maxn];
    int cnt, root;
    inline void up(int u) { // 维护
        a[u].size = a[a[u].ls].size + a[a[u].rs].size + a[u].count;
        a[u].hight = max(a[a[u].ls].hight, a[a[u].rs].hight) + 1;
        return;
    }
    int left_rotate(int u) { // 左旋
        int r = a[u].rs;
        a[u].rs = a[r].ls;
        a[r].ls = u;
        up(u);
        up(r);
        return r;
    }
    int right_rotate(int u) { // 右旋
        int l = a[u].ls;
        a[u].ls = a[l].rs;
        a[l].rs = u;
        up(u);
        up(l);
        return l;
    }
    int maintain(int u) { // 检查u为根的子树，违规即旋转调整，返回调整后的头
        int lh = a[a[u].ls].hight;
        int rh = a[a[u].rs].hight;
        if (lh - rh > 1) {
            if (a[a[a[u].ls].ls].hight >= a[a[a[u].ls].rs].hight) {
                u = right_rotate(u);
            } else {
                a[u].ls = left_rotate(a[u].ls);
                u = right_rotate(u);
            }
        } else if (rh - lh > 1) {
            if (a[a[a[u].rs].rs].hight >= a[a[a[u].rs].ls].hight) {
                u = left_rotate(u);
            } else {
                a[u].rs = right_rotate(a[u].rs);
                u = left_rotate(u);
            }
        }
        return u;
    }
    int add(int u, int num) {
        if (u == 0) {
            cnt++;
            a[cnt].key = num;
            a[cnt].count = a[cnt].size = a[cnt].hight = 1;
            return cnt;
        }
        if (a[u].key == num) {
            a[u].count++;
        } else if (a[u].key < num) {
            a[u].rs = add(a[u].rs, num);
        } else {
            a[u].ls = add(a[u].ls, num);
        }
        up(u);
        return maintain(u);
    }
    void add(int num) {
        root = add(root, num);
        return;
    }
    int small(int u, int num) {
        if (u == 0) {
            return 0;
        }
        if (a[u].key >= num) {
            return small(a[u].ls, num);
        } else {
            return a[u].count + a[a[u].ls].size + small(a[u].rs, num);
        }
    }
    int rank(int num) {
        return small(root, num) + 1;
    }
    int remove_mostlft(int u, int mostlft) {
        if (u == mostlft) {
            return a[u].rs;
        } else {
            a[u].ls = remove_mostlft(a[u].ls, mostlft);
            up(u);
            return maintain(u);
        }
    }
    int remove(int u, int num) {
        if (a[u].key < num) {
            a[u].rs = remove(a[u].rs, num);
        } else if (a[u].key > num) {
            a[u].ls = remove(a[u].ls, num);
        } else {
            if (a[u].count > 1) {
                a[u].count--;
            } else {
                if (a[u].ls == 0 && a[u].rs == 0) {
                    return 0;
                } else if (a[u].ls != 0 && a[u].rs == 0) {
                    u = a[u].ls;
                } else if (a[u].rs != 0 && a[u].ls == 0) {
                    u = a[u].rs;
                } else {
                    int mostlft = a[u].rs;
                    while (a[mostlft].ls) {
                        mostlft = a[mostlft].ls;
                    }
                    a[u].rs = remove_mostlft(a[u].rs, mostlft);
                    a[mostlft].ls = a[u].ls;
                    a[mostlft].rs = a[u].rs;
                    u = mostlft;
                }
            }
        }
        up(u);
        return maintain(u);
    }
    void remove(int num) {
        if (rank(num) != rank(num + 1)) {
            root = remove(root, num);
        }
        return;
    }
    int index(int u, int x) {
        if (a[a[u].ls].size >= x) {
            return index(a[u].ls, x);
        } else if (a[a[u].ls].size + a[u].count < x) {
            return index(a[u].rs, x - a[a[u].ls].size - a[u].count);
        }
        return a[u].key;
    }
    int index(int x) {
        return index(root, x);
    }
    int pre(int u, int x) {
        if (u == 0) {
            return -inf;
        }
        if (a[u].key >= x) {
            return pre(a[u].ls, x);
        } else {
            return max(a[u].key, pre(a[u].rs, x));
        }
    }
    int pre(int x) {
        return pre(root, x);
    }
    int nxt(int u, int x) {
        if (u == 0) {
            return inf;
        }
        if (a[u].key <= x) {
            return nxt(a[u].rs, x);
        } else {
            return min(a[u].key, nxt(a[u].ls, x));
        }
    }
    int nxt(int x) {
        return nxt(root, x);
    }
    bool in(int x) {
        return rank(x) != rank(x + 1);
    }
} avl_tree;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    int opt, x;
    int cnt = 0;
    while (n--) {
        cin >> opt >> x;
        if (opt == 1) {
            if (avl_tree.rank(x) != avl_tree.rank(x + 1)) {
                cout << "Already Exist" << '\n';
            } else {
                avl_tree.add(x);
                cnt++;
            }
        }
        if (opt == 2) {
            if (!cnt) {
                cout << "Empty" << '\n';
                continue;
            }
            if (avl_tree.rank(x) != avl_tree.rank(x + 1)) {
                cout << x << '\n'; 
                avl_tree.remove(x);
                cnt--;
            } else {
                int a = avl_tree.pre(x);
                int b = avl_tree.nxt(x);
                int l = inf, r = inf;
                if (avl_tree.in(a)) {
                    l = x - a;
                }
                if (avl_tree.in(b)) {
                    r = b - x;
                }
                if (l <= r) {
                    cout << a << '\n'; 
                    avl_tree.remove(a);
                } else {
                    cout << b << '\n'; 
                    avl_tree.remove(b);
                }
                    
                cnt--;
            }
        }
    }
    return 0;
}