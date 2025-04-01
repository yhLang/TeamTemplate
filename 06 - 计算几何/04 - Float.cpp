template <class T>
class FloatPointNumber {
    static constexpr T EPS = 1e-12;

    static_assert(EPS >= 0, "EPS < 0");

    static constexpr int sgn(T x) {
        return x < -EPS ? -1 : x > EPS;
    }

    static int precision;
    static string inputStr;

    T x;

public:
    constexpr FloatPointNumber() : x{} {}
    constexpr FloatPointNumber(T x) : x{x} {}

    constexpr T val() const {
        return x;
    }

    constexpr int sgn() const {
        return sgn(x);
    }

    template <class G>
    constexpr G round() const {
        return G(x + 0.5);
    }

    static constexpr void setprecision(int len) {
        precision = len;
    }

    // 四则运算

    constexpr FloatPointNumber &operator+=(FloatPointNumber a) & {
        x += a.x;
        return *this;
    }

    friend constexpr FloatPointNumber operator+(FloatPointNumber a, FloatPointNumber b) {
        return a += b;
    }

    constexpr FloatPointNumber operator-() const {
        return FloatPointNumber(-x);
    }

    constexpr FloatPointNumber &operator-=(FloatPointNumber a) & {
        x -= a.x;
        return *this;
    }

    friend constexpr FloatPointNumber operator-(FloatPointNumber a, FloatPointNumber b) {
        return a -= b;
    }

    constexpr FloatPointNumber &operator*=(FloatPointNumber a) & {
        x *= a.x;
        return *this;
    }

    friend constexpr FloatPointNumber operator*(FloatPointNumber a, FloatPointNumber b) {
        return a *= b;
    }

    constexpr FloatPointNumber &operator/=(FloatPointNumber a) & {
        x /= (long double)a.x;
        return *this;
    }

    friend constexpr FloatPointNumber operator/(FloatPointNumber a, FloatPointNumber b) {
        return a /= b;
    }

    // 比较运算

    friend constexpr int operator<(FloatPointNumber a, FloatPointNumber b) {
        return sgn(a.x - b.x) < 0;
    }

    friend constexpr int operator<=(FloatPointNumber a, FloatPointNumber b) {
        return sgn(a.x - b.x) <= 0;
    }

    friend constexpr int operator>(FloatPointNumber a, FloatPointNumber b) {
        return sgn(a.x - b.x) > 0;
    }

    friend constexpr int operator>=(FloatPointNumber a, FloatPointNumber b) {
        return sgn(a.x - b.x) >= 0;
    }

    friend constexpr bool operator==(FloatPointNumber a, FloatPointNumber b) {
        return sgn(a.x - b.x) == 0;
    }

    friend constexpr bool operator!=(FloatPointNumber a, FloatPointNumber b) {
        return sgn(a.x - b.x) != 0;
    }

    // 函数运算

    friend constexpr FloatPointNumber sqrtl(FloatPointNumber a) {
        if (a.val() <= 0) {
            return 0;
        }
        return FloatPointNumber(sqrtl(a.x));
    }

    friend constexpr FloatPointNumber sinl(FloatPointNumber a) {
        return FloatPointNumber(sinl(a.x));
    }

    friend constexpr FloatPointNumber cosl(FloatPointNumber a) {
        return FloatPointNumber(cosl(a.x));
    }

    friend constexpr FloatPointNumber abs(FloatPointNumber a) {
        return FloatPointNumber(fabs(a.x));
    }

    // 输入输出

    friend constexpr istream &operator>>(istream &is, FloatPointNumber &a) {
        is >> inputStr;
        if constexpr (is_same<T, long double>::value) {
            a = FloatPointNumber(stold(inputStr));
        } else {
            a = FloatPointNumber(stod(inputStr));
        }
        return is;
    }

    friend constexpr ostream &operator<<(ostream &os, FloatPointNumber a) {
        return os << fixed << std::setprecision(precision) << a.val();
    }

    // 常数
};

template <class T>
string FloatPointNumber<T>::inputStr;

template <class T>
int FloatPointNumber<T>::precision = 8;

using Float = FloatPointNumber<double>;