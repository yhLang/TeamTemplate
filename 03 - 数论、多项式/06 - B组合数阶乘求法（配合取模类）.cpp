template <class T>
class Comb {
    int n;
    vector<T> _jc, _ijc, _inv;

public:
    constexpr Comb() : n{0}, _jc{1}, _ijc{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }

    void init(int m) {
        m = min(m, T::getMod() - 1);
        if (m <= n)
            return;

        _jc.resize(m + 1);
        _ijc.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _jc[i] = _jc[i - 1] * i;
        }
        _ijc.back() = _jc.back().inv();
        for (int i = m; i > n; i--) {
            _ijc[i - 1] = _ijc[i] * i;
            _inv[i] = _ijc[i] * _jc[i - 1];
        }

        n = m;
    }

    T jc(int x) {
        if (x > n)
            init(x << 1);
        return _jc[x];
    }
    T ijc(int x) {
        if (x > n)
            init(x << 1);
        return _ijc[x];
    }
    T inv(int x) {
        if (x > n)
            init(x << 1);
        return _inv[x];
    }

    T A(int a, int b) {
        if (a < b or b < 0)
            return 0;
        return jc(a) * ijc(a - b);
    }
    T C(int a, int b) {
        if (a < b or b < 0)
            return 0;
        return A(a, b) * ijc(b);
    }
};

Comb<Z> comb;

