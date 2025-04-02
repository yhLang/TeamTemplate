class InPoly {
    
    // Seg c-d is Cross Seg a-b
    bool isCross(Point a, Point b, Point c, Point d) const {
        Vector ab = b - a, cd = d - c;
        if (ab.cross(cd) == 0)
            return 0; // 共线,寄
        int r1 = sgn(ab.cross(c - a)), r2 = sgn(ab.cross(d - a));
        int g1 = sgn(cd.cross(a - c)), g2 = sgn(cd.cross(b - c));
        return !(r1 * r2 > 0 or r1 + r2 == -1 or g1 * g2 > 0);
        // 真相交或者 c-d 贴着 a-b 左边
    }

public:
    // a IN/OUT/ON Polygon
    string operator()(Point a, const PS &ps) const {
        int res = 0;
        Vector b = {1 << 30, a.y};
        for (int i = 0; i < ps.size(); i++) {
            int j = (i + 1) % ps.size();
            if (onSeg(a, ps[i], ps[j]))
                return "ON";
            res += isCross(a, b, ps[i], ps[j]);
        }
        return (res % 2 ? "IN" : "OUT");
    }
};
const InPoly inPoly;

// a IN/OUT/ON Convex
string inConvex(Point a, const PS &ps) {
    if (a == ps[0])
        return "ON";
    if (ps.size() <= 1)
        return "OUT";
    if (ps.size() == 2)
        return onSeg(a, ps[0], ps[1]) ? "ON" : "OUT";
    auto v = a - ps[0];
    if ((ps[1] - ps[0]).cross(v) < 0 or (ps.back() - ps[0]).cross(v) > 0)
        return "OUT";
    int l = 1, r = ps.size() - 1;
    while (l + 1 < r) {
        auto mid = l + r >> 1;
        auto res = (ps[mid] - ps[0]).cross(v);
        if (res == 0)
            return (ps[mid] == a ? "ON" : (onSeg(a, ps[0], ps[mid]) ? "IN" : "OUT"));
        (res > 0 ? l : r) = mid;
    }
    auto res = (ps[r] - ps[l]).cross(a - ps[l]);
    if (res == 0 or onSeg(a, ps[0], ps[l]) or onSeg(a, ps[0], ps[r]))
        return "ON";
    return (res > 0 ? "IN" : "OUT");
}