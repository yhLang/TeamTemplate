template <class F, int Base, int M>
class BaseMask {
public:
    // 构造函数：直接以初始状态构造，状态内部固定使用 M 位
    BaseMask(F init = 0) : mask(init) {}

    // 查询位置 pos（0-indexed，0 为最低位）的数字
    int get(size_t pos) const {
        assert(pos < M);
        return (mask / s_pow[pos]) % Base;
    }

    // 修改位置 pos（0-indexed）的数字为 value，要求 value 在 [0, Base-1] 范围内
    void set(size_t pos, int value) {
        int cur = get(pos);
        mask += (value - cur) * s_pow[pos];
    }

    // 返回整个状态的字符串表示（低位在前，高位在后）
    string toString() const {
        string s;
        s.reserve(M);
        for (size_t pos = 0; pos < M; pos++) {
            s.push_back('0' + get(pos));
        }
        return s;
    }

    // 返回压缩后的状态（可用于进一步运算或调试）
    F getMask() const {
        return mask;
    }

private:
    F mask;

    // 静态幂数组，预处理计算 Base^0, Base^1, ... Base^M
    static vector<F> s_pow;
};

// 静态成员初始化：预处理计算从 0 次幂到 M 次幂
template <class F, int Base, int M>
vector<F> BaseMask<F, Base, M>::s_pow = []{
    vector<F> v(M + 1);
    v[0] = 1;
    for (size_t i = 1; i <= M; ++i) {
        v[i] = v[i - 1] * Base;
    }
    return v;
}();