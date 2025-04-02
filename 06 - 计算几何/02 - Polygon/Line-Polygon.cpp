PS cutPoly(const PS &ps, Point a, Point b) {
    // 返回多边形 ps 在有向直线 a->b 左边的部分
    PS v;
    auto c = b - a;
    for (int i = 0; i < ps.size(); i++) {
        int j = (i + 1) % ps.size();
        auto cr1 = c.cross(ps[i] - a), cr2 = c.cross(ps[j] - a);
        if (cr1 >= 0)
            v.push_back(ps[i]);
        if (sgn(cr1) * sgn(cr2) == -1)
            v.push_back(cross(a, b, ps[i], ps[j]));
    }
    return v;
}


// find point of tangency
class BinarySearchOnConvex {
    PS vs;

public:
    constexpr BinarySearchOnConvex(const PS &ps) : vs(ps.size()) {
        int n = size(ps);
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            vs[i] = ps[j] - ps[i];
        }
    }

    int operator()(Point a) const {
        auto polarcmp = [&](Vector p, Vector q) {
            if (sgn(p) == sgn(q)) {
                if (p.cross(q )== 0) {
                    return dis2(p) < dis2(q);
                } else {
                    return p.cross(q )> 0;
                }
            } else {
                return sgn(p) < sgn(q);
            }
        };

        int res = lower_bound(begin(vs), end(vs), a, polarcmp) - begin(vs);
        return res % size(vs);
    }
};