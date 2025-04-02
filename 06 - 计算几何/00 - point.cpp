template <class T, class G>
struct BaseVector2 : public pair<T, T> {
#define x first
#define y second

    using pair<T, T>::pair;

    BaseVector2 operator+(BaseVector2 a) const
    {
        return BaseVector2(this->x + a.x, this->y + a.y);
    }
    BaseVector2 operator-(BaseVector2 a) const
    {
        return BaseVector2(this->x - a.x, this->y - a.y);
    }
    BaseVector2 operator-() const
    {
        return BaseVector2(-this->x, -this->y);
    }
    G dot(BaseVector2 a) const
    {
        return G(this->x) * a.x + G(this->y) * a.y;
    }
    G cross(BaseVector2 a) const
    {
        return G(this->x) * a.y - G(this->y) * a.x;
    }
    BaseVector2 rotate() const
    {
        return BaseVector2(-this->y, this->x);
    }
    BaseVector2 rotate(double theta) const
    {
        BaseVector2 b(cosl(theta), sinl(theta));
        return BaseVector2(this->x * b.x - this->y * b.y,
            this->x * b.y + this->y * b.x);
    }

    int toLeft(const BaseVector2& a) const
    { // 1: left, 0 : on, -1 : right
        const auto t { (*this).cross(a) };
        return (t > 0) - (t < 0);
    }

    friend BaseVector2 operator*(const T& a, BaseVector2 b)
    {
        return BaseVector2(a * b.x, a * b.y);
    }
    friend istream& operator>>(istream& in, BaseVector2& p)
    {
        return in >> p.x >> p.y;
    }
    friend ostream& operator<<(ostream& ot, BaseVector2 p)
    {
        return ot << '(' << p.x << ", " << p.y << ')';
    }
};

template <class T, class G>
G dis2(BaseVector2<T, G> a, BaseVector2<T, G> b = BaseVector2<T, G>(0, 0))
{
    BaseVector2<T, G> p = a - b;
    return p.dot(p);
}
template <class T, class G>
auto dis(BaseVector2<T, G> a, BaseVector2<T, G> b = BaseVector2<T, G>(0, 0))
{
    return sqrtl(dis2(a, b));
}

template <class T, class G>
int sgn(BaseVector2<T, G> p)
{
    if (p.x < 0 or p.x == 0 and p.y > 0) {
        return 1;
    } else
        return 0;
    // 以41象限为先
}

template <class Vector>
bool polarCmp(Vector p, Vector q)
{
    if (sgn(p) == sgn(q)) {
        if (p.cross(q) == 0) {
            return dis2(p) < dis2(q);
        } else {
            return p.cross(q) > 0;
        }
    } else {
        return sgn(p) < sgn(q);
    }
}

using Point = BaseVector2<int, i64>;
using Vector = Point;
using PS = vector<Point>;

// 一个点延方向延长指定长度到的点
auto extend(BaseVector2<Float, Float> P, BaseVector2<Float, Float> dir, Float L) {
    const auto M = dis(dir);  // 计算方向向量的模长
    dir.x /= M; dir.y /= M;//转化成单位向量
    return P + L * dir;  // 按比例延长
}

