
RC[low][left] += tot;
RC[low][right + 1] -= tot;
RC[high + 1][left] -= tot;
RC[high + 1][right + 1] += tot;
R[low] += tot;
R[high + 1] -= tot;
C[left] += tot;
C[right + 1] -= tot;

for (int i = 0; i < n; i++) {
    R[i + 1] += R[i];
}
for (int j = 0; j < m; j++) {
    C[j + 1] += C[j];
}
for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (i > 0) {
        RC[i][j] += RC[i - 1][j];
    }
    if (j > 0) {
        RC[i][j] += RC[i][j - 1];
    }
    if (i > 0 and j > 0) {
        RC[i][j] -= RC[i - 1][j - 1];
    }
}