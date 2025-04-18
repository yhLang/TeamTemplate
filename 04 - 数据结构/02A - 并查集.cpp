struct DSU {
    int n;
    vector<int> f, siz;
    
    DSU() {}
    DSU(int _n) : n(_n) {
        init(_n);
    }
    
    void init(int n) {
        f.resize(n);
        iota(begin(f), end(f), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];//记住是y的信息合并到x上，x才是父亲
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }

    auto groups() {
        vector<int> find_buf(n), grp_siz(n);
        for (int i = 0; i < n; i++) {
            find_buf[i] = find(i);
            grp_siz[find_buf[i]] += 1;
        }
        vector res(n, vector<int>());
        for (int i = 0; i < n; i++) {
            res[i].reserve(grp_siz[i]);
        }
        for (int i = 0; i < n; i++) {
            res[find_buf[i]].push_back(i);
        }
        res.erase(
            remove_if(begin(res), end(res),
                           [&](const vector<int>& v) { return empty(v); }),
            end(res));
        return res;
    }

};