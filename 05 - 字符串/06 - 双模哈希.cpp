template <int D, array<int, D> B, array<int, D> P>
struct StringHash {
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
constexpr int HN = 2;
using Hash = StringHash<2, {133, 331}, {int(1e9 + 21), int(1e9 + 33)}>;
