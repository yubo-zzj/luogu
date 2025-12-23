#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
using ll = long long;
const ll p = 1e9 + 7;
ll read() {
    ll s = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch)) {
        s = (s << 3) + (s << 1) + (ch ^ 48);
        s %= (p - 1);
        ch = getchar();
    }
    return s;
}
struct matrix {
    ll a[2][2];
} Matrix1, Matrix2;
matrix multiply(matrix x, matrix y) {
    matrix z;
    z.a[0][0] = z.a[0][1] = z.a[1][0] = z.a[1][1] = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                z.a[i][j] += x.a[i][k] * y.a[k][j];
                z.a[i][j] %= p;
            }
        }
    }
    return z;
}
void out(matrix x) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << x.a[i][j] << " ";
        }
        cout << endl;
    }
    return;
}
matrix ksm(matrix di, ll zhi) {
    if (!zhi) {
        matrix x;
        x.a[0][0] = x.a[1][1] = 1;
        x.a[0][1] = x.a[1][0] = 0;
        return x;
    }
    if (zhi & 1) {
        return multiply(di, ksm(multiply(di, di), zhi >> 1));
    } else
        return ksm(multiply(di, di), zhi >> 1);
}
char N[maxn], M[maxn];
int lenn, lenm;
ll n, m, a, b, c, d;
void in() {
    cin >> N >> M >> a >> b >> c >> d;
    lenn = strlen(N), lenm = strlen(M);
    int p1 = p - (!(a == 1));
    for (int i = 0; i < lenm; ++i) {
        m = (m << 3) + (m << 1) + (M[i] - 48);
        m %= p1;
    }
    return;
}
void init() {
    in();
    Matrix1.a[0][0] = a;
    Matrix1.a[0][1] = b;
    Matrix1.a[1][0] = 0;
    Matrix1.a[1][1] = 1;
    Matrix2.a[0][0] = c;
    Matrix2.a[0][1] = d;
    Matrix2.a[1][0] = 0;
    Matrix2.a[1][1] = 1;
    return;
}
int main() {
    init();
    matrix x = multiply(ksm(Matrix1, m - 1), Matrix2);
    int p1 = p - (!(x.a[0][0] == 1));
    for (int i = 0; i < lenn; ++i) {
        n = (n << 1) + (n << 3) + (N[i] ^ 48);
        n %= p1;
    }
    matrix y = ksm(x, n - 1);
    y = multiply(y, ksm(Matrix1, m - 1));
    cout << (y.a[0][0] + y.a[0][1]) % p;
    return 0;
}