constexpr int P = 998244353;

template<class T>
T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

class Z {
using T = int;
private:
    T x;
    
    static T norm(T x) {
        if (x < 0) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    
public:
    Z(T x = 0) : x(norm(x)) {}
    Z(i64 x) : x(norm(x % P)) {}
    
    T val() const { return x; }
    
    Z operator-() const { return Z(norm(P - x)); }

    Z inv() const { 
        assert(x != 0); 
        return power(*this, P - 2); 
    }
    
    Z& operator*=(const Z& rhs) {
        x = static_cast<i64>(x) * rhs.x % P;
        return *this;
    }
    
    Z& operator+=(const Z& rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    
    Z& operator-=(const Z& rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    
    Z& operator/=(const Z& rhs) {
        return *this *= rhs.inv();
    }
    
    friend Z operator*(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    
    friend Z operator+(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    
    friend Z operator-(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    
    friend Z operator/(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    
    friend istream& operator>>(istream& is, Z& a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    
    friend ostream& operator<<(ostream& os, const Z& a) {
        return os << a.val();
    }
};
