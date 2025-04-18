unordered_map<int, Z> fMu;
vector<int> primes;
vector<Z> mu;

void sieve(int n) {
    mu.resize(n, inf<int>);
    primes.clear();
    
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (mu[i] == inf<int>) {
            mu[i] = -1;
            primes.push_back(i);
        }
        
        for (auto& pi : primes) {
            const auto now = i * pi;
            if (now > n) {
                break;
            }
            if (i % pi == 0) {// 若 pi 是 i 的最小质因子，则 now 存在平方因子，
                // 故 Möbius 函数值为 0，直接退出循环
                mu[now] = 0;
                break;
            }
            // 否则，按照 Möbius 函数的乘法性质，更新 mu[now] = -mu[i]
            mu[now] = -mu[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        mu[i] += mu[i - 1];
    }
}


Z sumMu(int n) {
    if (n <= N) {
        return mu[n];
    }
    if (fMu.count(n)) {
        return fMu[n];
    }
    if (n == 0) {
        return 0;
    }
    Z ans = 1;
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (r - l + 1) * sumMu(n / l);
    }
    return ans;
}

int main() {
    
    sieve(N);
    
    int L, R;
    cin >> L >> R;
    L -= 1;
    
    Z ans = 0;// 枚举 l 分块，利用区间划分优化求和
    // 这里的 l 是用于区分不同的倍数区间
    for (int l = 1, r; l <= R; l = r + 1) {
        r = R / (R / l); // 找到使得 R / l 值相同的最大区间端点 r
        if (l <= L) {// 如果 l 对应的区间也包含在 L 内，则确保 r 不超过 L 中相应区间的上界
            r = min(r, L / (L / l));
        }
        // 乘上 (sumMu(r) - sumMu(l - 1)) 表示区间内 Möbius 函数前缀和的变化
        ans += (power(Z(2), R / l - L / l) - 1) * (sumMu(r) - sumMu(l - 1));
    }
    
    cout << ans << "\n";
    
    return 0;
}

