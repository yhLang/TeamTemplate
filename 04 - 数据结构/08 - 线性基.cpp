template <class T>
struct LinearBasis {
    static constexpr int logn = __lg(numeric_limits<T>::max());
    array<T, logn + 1> b;
    int rank;
    bool canZero, dirt;
 
    LinearBasis() {
        clear();
    }
 
    void clear() {
        canZero = false;
        dirt = false;
        rank = 0;
        b.fill(0);
    }
 
    void insert(T x) {
        for (int i = logn; i >= 0; i--) {
            if (x >> i & 1) {
                if (b[i] == 0) {
                    b[i] = x;
                    rank += 1;
                    dirt = true;
                    return;
                }
                x ^= b[i];
            }
        }
        canZero = true;
    }
 
    // 询问线性基能不能异或出 x
    bool check(T x) {
        for (int i = logn; i >= 0; i--)
            if (x >> i & 1) {
                if (b[i] == 0) {
                    return false;
                }
                x ^= b[i];
            }
        return true;
    }
 
    T getMax() {
        T res = 0;
        for (int i = logn; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
 
    T getMin() {
        if (canZero) {
            return 0;
        }
        int k = 0;
        while (k <= logn and b[k] == 0) {
            k += 1;
        }
        assert(k <= logn);
        return b[k];
    }
 
    void build() {
        if (dirt == false) {
            return;
        }
        for (int i = 1; i <= logn; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (b[i] >> j & 1) {
                    b[i] ^= b[j];
                }
            }
        }
        dirt = true;
    }
 
    T getDiffCount() {
        return (T(1) << rank) - !canZero;
    }
 
    // 查询有 K 个元素比它小的元素
    T find_by_order(T K) {
        if (canZero == false) {
            K += 1;
        }
        build();
 
        T res = 0;
        int j = 0;
        for (int i = 0; i <= logn; i++) {
            if (b[i] == 0) {
                continue;
            }
 
            if (K >> j & 1) {
                res ^= b[i];
            }
            j += 1;
        }
 
        return res;
    }
};