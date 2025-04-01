constexpr i64 mod = 998244353;

template<int n, int m>
struct Matrix : array<array<i64, m>, n> {
    Matrix() : array<array<i64, m>, n>{} {}
    void id() {// 构造单位矩阵（对角线元素为 1，其余为 0）
        for (int i = 0; i < n; i++) (*this)[i][i] = 1;
    }
};
template<int n, int p, int m>
Matrix<n, m> operator*(const Matrix<n, p> &A, const Matrix<p, m> &B) {
    Matrix<n, m> C{};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                (C[i][j] += A[i][k] * B[k][j]) %= mod;
    return C;
}
template<int n> 
Matrix<n, n> power(Matrix<n, n> A, i64 b) {
    Matrix<n, n> r{};
    r.id();
    for (; b; b >>= 1, A = A * A)
        if (b & 1) r = r * A;
    return r;
}