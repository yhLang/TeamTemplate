template <class Info>
struct SegmentTree {
    const int n;
    vector<Info> info;
    SegmentTree(int n): n(n), info(4 << __lg(n)) {}
template <typename T>
    SegmentTree(vector<T> init) : SegmentTree(init.size()) {
        auto go = [&](auto go, int id, int l, int r) -> void {
            if (r - l == 1) {
                info[id] = {init[l]};
                return;
            }
            int m = l + r >> 1;
            go(go, 2 * id, l, m);
            go(go, 2 * id + 1, m, r);
            pull(id);
        };
        go(go, 1, 0, n);
    }
    void pull(int id) {
        info[id] = info[2 * id] + info[2 * id + 1];
    }
    void modify(int p, const Info &v) {
        auto go = [&](auto go, int id, int l, int r) -> void {
            if (r - l == 1) {
                info[id] = v;
                return;
            }
            int m = l + r >> 1;
            p < m ? go(go, 2 * id, l, m) : go(go, 2 * id + 1, m, r);
            pull(id);
        };
        go(go, 1, 0, n);
    }
    Info rangeQuery(int ql, int qr) {
        auto go = [&](auto go, int id, int l, int r) -> Info {
            if (qr <= l or r <= ql) {
                return Info();
            }
            if (ql <= l and r <= qr) {
                return info[id];
            }
            int m = l + r >> 1;
            return go(go, 2 * id, l, m) + go(go, 2 * id + 1, m, r);
        };
        return go(go, 1, 0, n);
    }
template <typename F>
    int findFirst(int ql, int qr, F f) {
        auto go = [&](auto go, int id, int l, int r) -> int {
            if (qr <= l or r <= ql or !f(info[id])) {
                return -1;
            }
            if (r - l == 1) {
                return l;
            }
            int m = l + r >> 1;
            int res = go(go, 2 * id, l, m);
            if (res == -1) {
                res = go(go, 2 * id + 1, m, r);
            }
            return res;
        };
        return go(go, 1, 0, n);
    }
template <typename F>
    int findLast(int ql, int qr, F f) {
        auto go = [&](auto go, int id, int l, int r) -> int {
            if (qr <= l or r <= ql or !f(info[id])) {
                return -1;
            }
            if (r - l == 1) {
                return l;
            }
            int m = l + r >> 1;
            int res = go(go, 2 * id + 1, m, r);
            if (res == -1) {
                res = go(go, 2 * id, l, m);
            }
            return res;
        };
        return go(go, 1, 0, n);
    }
};
 
struct Max {
    int x = 0;
};
 
Max operator+(Max a, Max b) {
    return {max(a.x, b.x)};
}