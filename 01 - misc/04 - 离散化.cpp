template <class T>
struct Discreter {
    vector<T> elementSet;

    Discreter(const vector<T> &a) : elementSet(a) {
        sort(begin(elementSet), end(elementSet));
        elementSet.erase(unique(begin(elementSet), end(elementSet)), end(elementSet));
    }

    vector<int> process(const vector<T> &a) const {//get the dicreter arr
        vector<int> discRes(a.size());

        for (int i = 0; i < a.size(); i++) {
            discRes[i] = query(a[i]);
        }

        return discRes;
    }

    int query(const T &x) const {
        auto it = lower_bound(begin(elementSet), end(elementSet), x);
        // assert(it != end(elementSet) and *it == x);

        return it - begin(elementSet);
    }

    int queryUpperBound(const T &x) const {
        auto it = upper_bound(begin(elementSet), end(elementSet), x);

        return it - begin(elementSet);
    }

    T queryInv(int index) const {
        return elementSet[index];
    }

    int size() {
        return elementSet.size();
    }
};