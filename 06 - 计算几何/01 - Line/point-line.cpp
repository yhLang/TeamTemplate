// a on Line b-c
bool onLine(Point a, Point b, Point c) {
    b = b - a, c = c - a;
    return b.cross(c)== 0;
}

// a on Seg b-c
bool onSeg(Point a, Point b, Point c) {
    b = b - a, c = c - a;
    return b.cross(c)== 0 and b.dot(c) <= 0;//b.dot(c)确保b, c在a两侧
}

// a disTo Line b-c
Float disToLine(Point a, Point b, Point c) {
    Point v1 = b - c, v2 = a - c;
    return 1.L * abs(v1.cross(v2)) / sqrtl(v1.dot(v1));
}

// a disTo Seg b-c
Float disToSeg(Point a, Point b, Point c) {
    if ((a - b).dot(c - b) <= 0 or (a - c).dot(b - c) <= 0) {
        return min(dis(a, b), dis(a, c));
    }
    return disToLine(a, b, c);
}

// a project to Line b-c (here Point = Point<Float, Float>)
Point foot(Point a, Point b, Point c) {
    Point u = a - b, v = c - b;
    return b + 1.L * (u.dot(v)) / (v.dot(v)) * v;
}

// a symmetry to Line b-c (here Point = Point<Float, Float>)
Point symmetry(Point a, Point b, Point c) {//对称点
    Point ft = foot(a, b, c);
    return 2 * ft - a;
}

// 求过点a且与b-c平行的直线的方向向量
pair<Point, Point> parallelLine(Point a, Point b, Point c) {
    // 计算方向向量 d = (c - b)
    Point d = c - b;
    
    // 返回与 b-c 平行且经过 a 的直线表示为两个点
    // 直线的一个点是 a，另一个点是 a + d
    return {a, a + d};
}

int toLeft(Vector v, Point p, Point &c) {//方向向量v，起点p，c是否在v的left
    return v.toLeft(c - p);//p->c，即直线始点到这个点的向量
} 