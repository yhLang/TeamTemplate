// 封装圆类
struct Circle {
    Point center;  // 圆心
    Float radius;  // 半径

    // 默认构造：构造一个圆心在原点、半径为0的退化圆
    Circle() : center(Point(0, 0)), radius(0) {}

    // 构造函数：给定圆心和半径
    Circle(const Point &center, const ld &radius) : center(center), radius(radius) {}

    // 构造函数：利用两点构造圆
    // 这里构造的圆以两点作为直径的两个端点
    Circle(const Point &a, const Point &b) {
        // 圆心为 a 和 b 的中点
        center = 0.5 * (a + b);
        // 半径为中点到任一端点的距离
        radius = dis(center, a);
    }

    // 构造函数：利用三个不共线点构造外接圆（Circumcircle）
    // 当三点共线时，可退化为两点构造的圆（此处以 a 和 c 构造）
    Circle(const Point &a, const Point &b, const Point &c) {
        // 若三点共线，则返回由两点构造的圆
        if ((b - a).cross(c - a) == 0) {
            // 退化为两点构造的圆
            center = 0.5 * (a + c);
            radius = dis(center, a);
        } else {
            // 计算边 ab 和 bc 的中点
            Point mid1 = 0.5 * (a + b);
            Point mid2 = 0.5 * (b + c);
            // 对应边的垂直方向（利用 rotate() 旋转 90 度得到垂直向量）
            Point perp1 = (b - a).rotate();
            Point perp2 = (c - b).rotate();
            // 利用两条垂直平分线求交点，得到外接圆的圆心
            center = cross(mid1, mid1 + perp1, mid2, mid2 + perp2);
            // 半径为圆心到任一点（此处选择 a）的距离
            radius = dis(center, a);
        }
    }

    // 判断某个点是否在圆内或圆上（利用距离函数 dis）
    bool contains(const Point &p) const {
        return dis(center, p) <= radius;
    }
};