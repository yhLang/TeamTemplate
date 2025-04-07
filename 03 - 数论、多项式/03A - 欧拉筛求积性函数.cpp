struct MultFunc {//欧拉筛法求积性函数
    const int n;              // 筛的上界 n（不包括 n 本身）
    vector<int> mpf;          // mpf[i] 存储 i 的最小质因子（若 i 为质数，则 mpf[i] = i），大小为 n
    vector<int> primes;       // 存储所有筛出（即小于 n）的质数
    vector<int> f; //要求的积性函数
    vector<int> cnt_mpf; // 最小质因子的次幂数

    // 构造函数：初始化筛法，计算所有小于 n 的质数和每个数的最小质因子
    MultFunc(int _n, function<int(int, int)> calcF) : n(_n), mpf(_n), f(_n), cnt_mpf(_n) {
        // calcF 是这个积性函数
        // 枚举每个数 i，从 2 开始（1 不是质数）
        f[1] = 1; 
        for (int i = 2; i < n; i++) {
            // 如果 mpf[i] 为 0，则 i 还未被筛过，说明 i 为质数
            if (mpf[i] == 0) {
                primes.push_back(i);  // 将 i 加入质数列表
                mpf[i] = i;           // 质数 i 的最小质因子就是它本身
                f[i] = calcF(i, 1);  // 计算该质数的积性函数
                cnt_mpf[i] = 1;      
            }
            // 对于每个已筛出的质数 pi，将 i * pi 标记为合数，并记录最小质因子
            for (auto& pi : primes) {
                const auto now = i * pi;//现在要筛的
                if (now > n) {break;}
                mpf[now] = pi; // 更新 now 的最小质因子为 pi
                // 如果 pi 恰好是 i 的最小质因子，则结束内层循环，保证每个合数只被更新一次
                if (pi == mpf[i]) {
                    cnt_mpf[now] = cnt_mpf[i] + 1;//从上一个递推过来
                    f[now] = f[i] / calcF(pi, cnt_mpf[i]) * calcF(pi, cnt_mpf[now]);//除掉上一个原来的次，乘上现在的次
                    break;
                }
                //说明 pi 在 now 中的次数为 1
                cnt_mpf[now] = 1;
                f[now] = f[i] * calcF(pi, 1); 
            }
        }
    }
};

constexpr int N = int(1E7) + 5;
const MultFunc get_d(N, [](int p, int k) {//求因子个数，那么就是次幂 + 1,跟 p 无关了
    return k + 1;
});
const auto& d = get_d.f;