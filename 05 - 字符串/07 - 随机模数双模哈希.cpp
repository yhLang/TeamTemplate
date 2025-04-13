mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
bool isprime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}
 
int findPrime(int n) {
    while (!isprime(n))
        n++;
    return n;
}

template <int D>
struct StringHash {
    static array<int, D> B;
    static array<int, D> P;
    vector<array<int, D>> h;

    template <class T>
    StringHash(const T &s) : h(size(s) + 1) {
        for (int i = 0; i < size(s); i++) {
            for (int k = 0; k < D; k++) {
                h[i + 1][k] = (1ll * h[i][k] * B[k] + s[i] + 1) % P[k];
            }
        }
    }

    // [l, r)
    array<int, D> get(int l, int r) {
        static vector<array<int, D>> spow(1);
        if (r - l < 0)
            throw -1;

        if (spow.size() < r - l + 1) {
            if (spow[0][0] == 0) {
                spow[0].fill(1);
            }
            int n = spow.size();
            spow.resize(r - l + 1);
            for (int i = n; i < spow.size(); i++) {
                for (int k = 0; k < D; k++) {
                    spow[i][k] = 1ll * spow[i - 1][k] * B[k] % P[k];
                }
            }
        }

        array<int, D> res = {};
        for (int k = 0; k < D; k++) {
            res[k] = h[r][k] - 1ll * h[l][k] * spow[r - l][k] % P[k];
            res[k] += (res[k] < 0 ? P[k] : 0);
        }
        return res;
    }
};
constexpr int D = 2;
template<>
array<int, 2> StringHash<D>::P{findPrime(rng() % 900000000 + 100000000),findPrime(rng() % 900000000 + 100000000)};
template<>
array<int, 2> StringHash<D>::B{13331, 131};
using Hash = StringHash<D>;
