template<class T>
T area(const PS &ps) {
    T res = 0;
    for (auto i = 0U; i < psize(s); i++) {
        int j = (i + 1) % (psize(s));
        res += ps[i].cross(ps[j]);
    }
    return res / 2;
}