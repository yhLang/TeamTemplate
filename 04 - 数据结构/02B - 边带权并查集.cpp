template <class T>
struct DSU {
    vector<int> f;
    vector<int> size;
    vector<T> w;

    DSU(int n) : f(n), size(n), w(n) {
        iota(begin(f), end(f), 0);
        fill(begin(size), end(size), 1);
    }

    int find(int x) {
        if (f[x] == x) {return x;}
        int pr{f[x]}, anc{find(pr)};
        w[x] = w[x] + w[pr];
        return f[x] = anc;
    }

    void Union(int x, int y, const T &z) {
        T road {w[x] + z}, lastWy {w[y]};
        
        x = find(x), y = find(y);

        if (x == y) {return;}

        w[y] = road - lastWy;

        size[x] += size[y];
        f[y] = x;
    }
};

struct Info {
    int val;

    Info(int x = 0) : val(x) {}

    bool operator==(const Info &a) const {
        return val == a.val;
    }

    Info operator+(const Info &a) const {
    }

    Info operator-(const Info &a) const {
    }
};