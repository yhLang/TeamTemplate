template <class T, class Cmp = less<T>>
class RMQ {
    const int n;
    const int logn;

    const Cmp cmp = Cmp();
    vector<vector<T>> jump;
public:
    constexpr RMQ(const vector<T> &a)
        : n{(int)size(a)}, logn{__lg(n)}, jump(logn + 1) {

        jump[0] = a;

        for (int j = 1; j <= logn; j++) {
            jump[j].resize(n - (1 << j) + 1);
        }

        for (int j = 0; j < logn; j++) {
            const int limit = n - (1 << (j + 1));
            for (int i = 0; i <= limit; i++) {
                jump[j + 1][i] = min(jump[j][i], jump[j][i + (1 << j)], cmp);
            }
        }
    }

    // [l, r)
    constexpr T operator()(int l, int r) const {
        assert(l < r and r <= n);
        int log = __lg(r - l);
        return min(jump[log][l], jump[log][r - (1 << log)], cmp);
    }
};