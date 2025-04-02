template <class T>
class PrefixSum {
    std::vector<T> preSum;

public:
    template <class G>
    PrefixSum(const std::vector<G>& a)
        : preSum(a.size() + 1)
    {
        for (int i = 0; i < a.size(); i++) {
            preSum[i + 1] = preSum[i] + a[i];
        }
    }
    T operator()(int l, int r) { return preSum[r] - preSum[l]; }
    T operator()(int r) { return preSum[r]; }
};

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
