// 高维前缀和/子集和
for (int i = 0; i < (1 << D); i++) {
    dp[i] = a[i];
}
for (int d = 0; d < D; d++) {
    for (int i = 0; i < (1 << D); i++) {
        if (i & (1 << d)) {
            dp[i] += dp[i ^ (1 << d)];
        }
    }
}

// 高维后缀和/超集和
for (int i = 0; i < (1 << D); i++) {
    dp[i] = a[i];
}
for (int d = 0; d < D; d++) {
    for (int i = 0; i < (1 << D); i++) {
        if (!(i & (1 << d))) {
            dp[i] += dp[i ^ (1 << d)];
        }
    }
}