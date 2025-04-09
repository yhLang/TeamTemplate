template <class T>
struct Discreter {
    vector<T> lsh;

    Discreter(const vector<T> &a) : lsh(a) {
        sort(begin(lsh), end(lsh));
        lsh.erase(unique(begin(lsh), end(lsh)), end(lsh));
    }

    vector<int> process(const vector<T> &a) const {//get the dicreter arr
        vector<int> discRes(a.size());

        for (int i = 0; i < a.size(); i++) {
            discRes[i] = query(a[i]);
        }

        return discRes;
    }

    int query(const T &x) const {
        auto it = lower_bound(begin(lsh), end(lsh), x);
        // assert(it != end(lsh) and *it == x);

        return distance(begin(lsh), it);
    }

    int queryUpperBound(const T &x) const {
        auto it = upper_bound(begin(lsh), end(lsh), x);

        return distance(begin(lsh), it);
    }

    T queryInv(int i) const {
        return lsh[i];
    }

    int size() {
        return lsh.size();
    }
};