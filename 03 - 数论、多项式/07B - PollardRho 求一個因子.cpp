template <class T>
class PollardRho {
    using R = ModuloInteger<T, 0>;
    mt19937_64 rng{static_cast<unsigned long long>(chrono::steady_clock::now().time_since_epoch().count())};
    MillerRabin<T> rabin;

    static constexpr T gcd(T a, T b) {
        return b == 0 ? a : gcd(b, a % b);
    }

public:
    // 返回 n 的随机一个[2, n-1]内的因子, 或者判定是质数
    T findFactor(T n) {
        assert(n >= 2);
        if (n % 2 == 0) {
            return 2;
        }
        if (rabin(n)) {
            return n;
        }

        R::setMod(n);
        while (true) {
            T c = rng() % (n - 1) + 1;
            auto f = [&](R x) { return x * x + c; };
            R t = 0, r = 0;
            R p = 1, q;
            do {
                for (int i = 0; i < 128; i++) {
                    t = f(t);
                    r = f(f(r));
                    if (t == r or (q = p * abs(T(t) - T(r))) == 0) {
                        break;
                    }
                    p = q;
                }
                T d = gcd(T(p), n);
                if (d > 1) {
                    return d;
                }
            } while (t != r);
        }
    }

    vector<pair<T, int>> primeFactorize(T x) {
        assert(x >= 2);
        vector<T> ps;
        vector<T> stk = {x};
        while (!stk.empty()) {
            x = stk.back();
            stk.pop_back();

            T y = findFactor(x);
            if (x == y) {
                ps.push_back(x);
            } else {
                stk.push_back(y);
                stk.push_back(x / y);
            }
        }

        sort(begin(ps), end(ps));
        vector<pair<T, int>> pc;
        for (T p : ps) {
            if (pc.empty() or pc.back().first != p) {
                pc.emplace_back(p, 1);
            } else {
                pc.back().second += 1;
            }
        }

        return pc;
    }
};
PollardRho<long long> rho;