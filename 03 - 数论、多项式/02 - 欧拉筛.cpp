// Sieve 结构体实现了一个线性筛（Linear Sieve），用于求解小于 n 的所有质数以及最小质因子（Minimum Prime Factor）。
struct Sieve {
    const int n;              // 筛的上界 n（不包括 n 本身）
    vector<int> mpf;          // mpf[i] 存储 i 的最小质因子（若 i 为质数，则 mpf[i] = i），大小为 n
    vector<int> primes;       // 存储所有筛出（即小于 n）的质数

    // 构造函数：初始化筛法，计算所有小于 n 的质数和每个数的最小质因子
    Sieve(int n) : n{n}, mpf(n) {
        // 枚举每个数 i，从 2 开始（1 不是质数）
        for (int i = 2; i < n; i++) {
            // 如果 mpf[i] 为 0，则 i 还未被筛过，说明 i 为质数
            if (mpf[i] == 0) {
                primes.push_back(i);  // 将 i 加入质数列表
                mpf[i] = i;           // 质数 i 的最小质因子就是它本身
            }
            // 对于每个已筛出的质数 primes[j]，将 i * primes[j] 标记为合数，并记录最小质因子
            for (int j = 0; j < primes.size() and i * primes[j] < n; j++) {
                mpf[i * primes[j]] = primes[j]; // 更新 i * primes[j] 的最小质因子为 primes[j]
                // 如果 primes[j] 恰好是 i 的最小质因子，则结束内层循环，保证每个合数只被更新一次
                if (primes[j] == mpf[i]) {
                    break;
                }
            }
        }
    }

    // 模板函数：对任意类型 T 的 x 进行质因数分解，返回 (质因子, 指数) 的向量
    template <class T>
    vector<pair<T, int>> primeFactorize(T x) const {
        // x 至少应为 1
        assert(x >= 1);
        // 用于存储质因数分解结果，格式为 {质因子, 指数}
        vector<pair<T, int>> ps;

        // lambda 函数 process：对某个质因子 d 进行处理，统计 d 在 x 中出现的次数
        auto process = [&](int d) {
            assert(d >= 2);
            int cnt = 0;
            // 除尽 x 中所有的 d
            while (x % d == 0) {
                x /= d;
                cnt += 1;
            }
            // 将 (质因子, 指数) 加入结果列表
            ps.emplace_back(d, cnt);
        };

        // 先利用预先筛好的质数进行尝试分解
        for (int d : primes) {
            // 若 x 小于 n 或 d 超过 sqrt(x) 则退出循环（此时剩余 x 要么较小，可以利用 mpf 继续分解，要么 x 本身为质数）
            if (x < n or 1LL * d * d > x) {
                break;
            }
            // 如果 x 能被质数 d 整除，则进行处理
            if (x % d == 0) {
                process(d);
            }
        }

        // 如果 x 仍然比较大（>= n），则直接从 n 开始枚举可能的因子
        // 这个循环用于分解那些大于等于 n 的质因子（可能不在预先筛选的范围内）
        for (int d = n; 1LL * d * d <= x and x >= n; d++) {
            if (x % d == 0) {
                process(d);
            }
        }

        // 如果 x 已经小于 n，那么可以利用 mpf 数组快速分解剩余部分
        if (x < n) {
            // 当 x 仍大于 1 时，通过 mpf[x] 反复分解 x
            while (x > 1) {
                int d = mpf[x]; // 获取 x 的最小质因子
                process(d);
            }
        }

        // 如果剩余的 x 仍大于 1，则它必然是一个质数，直接加入结果
        if (x > 1) {
            ps.emplace_back(x, 1);
        }

        return ps;
    }

    // 模板函数：返回 x 的所有因子（先进行质因数分解，然后根据分解结果枚举所有因子）
    template <class T>
    vector<T> allFactors(T x) const {
        return allFactors(primeFactorize(x));
    }

    // 静态模板函数：根据质因数分解结果 ps 枚举所有因子
    template <class T>
    static vector<T> allFactors(const vector<pair<T, int>> &ps) {
        // 初始化因子集合，初始只有 1
        vector<T> ds = {1};
        // 对于每个质因子及其指数
        for (auto [d, cnt] : ps) {
            // 记录当前 ds 的区间边界
            int l = 0, r = ds.size();
            // 对每个质因子 d，重复乘上 d 共 cnt 次
            while (cnt--) {
                // 枚举当前已有的所有因子，并将它们乘以 d 后加入 ds 中
                for (int k = l; k < r; k++) {
                    ds.push_back(ds[k] * d);
                }
                // 更新区间边界，确保下一次只扩展新加入的因子
                l = r, r = ds.size();
            }
        }

        return ds;
    }
};

// 定义筛的上界 N，取值为 2×10^6 + 5
constexpr int N = int(2E6) + 5;
// 全局常量 si 为 Sieve 类型的实例，预先筛选出小于 N 的质数和最小质因子
const Sieve si(N);
