// Line a-b cross Line c-d
Point cross(Point a, Point b, Point c, Point d) {
    Point v = c - d;
    Float sa = v % (a - d), sb = (b - d) % v;
    return sa / (sa + sb) * (b - a) + a;
}

// a-b 和 a-c 的夹角 signed
Float getAngle(Point a, Point b, Point c) {
    auto v1 = b - a, v2 = c - a;
    return atan2l(v1.cross(v2), v1.dot(v2)); // ∠bac
}

// 对四个不同的点判断四点共圆
// d在abc外接圆外return 1, 内return -1
int inCircle(Point a, Point b, Point c, Point d) {
    const Float PI = numbers::pi;
    Float ag1 = getAngle(a, b, c), ag2 = getAngle(d, c, b);
    auto sgn = [](Float x) { return x < 0 ? -1 : (x > 0); };
    if (sgn(ag1) == sgn(ag2)) {
        return sgn(PI - std::abs(ag1 + ag2));
    } else {
        return sgn(std::abs(ag1) - std::abs(ag2));
    }
}

// 判断两线段 [a,b] 与 [c,d] 是否相交
bool segmentsIntersect(Point a, Point b, Point c, Point d) {
    // 计算向量叉积，判断 c 与 d 相对于线段 a-b 的位置
    auto d1 = (b - a).cross(c - a);
    auto d2 = (b - a).cross(d - a);
    // 计算向量叉积，判断 a 与 b 相对于线段 c-d 的位置
    auto d3 = (d - c).cross(a - c);
    auto d4 = (d - c).cross(b - c);

    // 如果 c 与 d 分别在 a-b 的两侧，且 a 与 b 分别在 c-d 的两侧，则两线段严格相交
    if (((d1 > 0 and d2 < 0) or (d1 < 0 and d2 > 0)) and
        ((d3 > 0 and d4 < 0) or (d3 < 0 and d4 > 0)))
        return true;

    // 若有共线情况，则判断对应点是否在线段上
    if (d1 == 0 and onSeg(c, a, b)) return true;
    if (d2 == 0 and onSeg(d, a, b)) return true;
    if (d3 == 0 and onSeg(a, c, d)) return true;
    if (d4 == 0 and onSeg(b, c, d)) return true;

    return false;
}

bool noIntersection(int x1, int y1, int x2, int y2, 
                    int x3, int y3, int x4, int y4) {
    // 判断矩形 A (x1, y1, x2, y2) 和矩形 B (x3, y3, x4, y4) 是否没有相交
    // 1. A 在 B 的左侧 (A 的右边界 <= B 的左边界)
    // 2. A 在 B 的右侧 (A 的左边界 >= B 的右边界)
    // 3. A 在 B 的下方 (A 的上边界 <= B 的下边界)
    // 4. A 在 B 的上方 (A 的下边界 >= B 的上边界)
    return x2 <= x3 || x4 <= x1 || y2 <= y3 || y4 <= y1;
}
