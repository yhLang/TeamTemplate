// 如果模数不为质数！！或者给定模数！！，最好用递推
vector C(n + 1, vector<Z>(n + 1));
C[0][0] = 1;
for (int i = 1; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= n; j++) {
        C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}