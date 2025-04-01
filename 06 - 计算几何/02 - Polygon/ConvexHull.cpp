PS convex(PS ps) {
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());

    const int n = ps.size();
    if (n <= 1) {
        return ps;
    }

    PS hull(n + 1);
    int k = -1;

    for (int i = 0; i < n; i++) {
        while (k >= 1 and (hull[k] - hull[k - 1]).cross(ps[i] - hull[k]) <= 0) {
            k -= 1;
        }
        hull[++k] = ps[i];
    }

    for (int i = n - 2, m = k + 1; i >= 0; i--) {
        while (k >= m and (hull[k] - hull[k - 1]).cross(ps[i] - hull[k]) <= 0) {
            k -= 1;
        }
        hull[++k] = ps[i];
    }

    assert(k >= 2);
    return hull.resize(k), hull;
}

template <class T>
pair<T, T> minmaxTriangle(const PS& vec)
{
    int n { (int)(size(vec)) }; if (n <= 2) {return { 0, 0 };}
    
    T maxans = 0, minans = numeric_limits<T>::max(); 

    using pii = pair<int, int>; vector<pii> evt; {//维护线段事件
        evt.reserve(n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) if (i != j) {
                if (vec[i] == vec[j]) { // 有重点，所以可以直接为0
                    minans = 0;
                } else {
                    evt.emplace_back(i, j);
                }
            }
        }
        sort(begin(evt), end(evt), [&](const pii& u, const pii& v) {//对旋转后的向量排极角序
            const Point du = vec[u.second] - vec[u.first], dv = vec[v.second] - vec[v.first];
            return polarCmp<Point>({ du.y, -du.x }, { dv.y, -dv.x });
        });
    }
    
    vector<int> vx(n); {//维护该点在x大小关系中的位置
        iota(begin(vx), end(vx), 0);
        sort(begin(vx), end(vx), [&](int x, int y) { return vec[x] < vec[y]; });
    }

    vector<int> pos(n); {for (int i = 0; i < ssize(vx); i++) {pos[vx[i]] = i;}}//维护索引

    for (auto now : evt) {//按照极角序遍历线段模拟旋转
        auto u = now.first, v = now.second;
        const int i = pos[u], j = pos[v];//找出这个线段左右端点在x轴的大小位置
        const int _i = min(i, j), _j = max(i, j);
        const Point vecu = vec[u], vecv = vec[v];
        if (_i > 0) {//用左最近更新最小答案（左相邻）
            minans = min(minans, abs((vec[vx[_i - 1]] - vecu).cross(vec[vx[_i - 1]] - vecv)));
        }
        if (_j < ssize(vx) - 1) {//用右最近更新最小答案（右相邻）
            minans = min(minans, abs((vec[vx[_j + 1]] - vecu).cross(vec[vx[_j + 1]] - vecv)));
        }
        //用最左或者最右更新最大答案
        maxans = max({ maxans, abs((vec[vx[0]] - vecu).cross(vec[vx[0]] - vecv)), abs((vec[vx.back()] - vecu).cross(vec[vx.back()] - vecv)) });
        if (i < j) {swap(vx[i], vx[j]); pos[u] = j; pos[v] = i;}//旋转后大小关系会交换
    }
    return { minans, maxans };
}

auto nxt = [&](int i) {return i == m - 1 ? 0 : i + 1;};

//求凸包直径
auto cv{convex(ps)}; int m{(int)size(cv)}; 
auto area = [&](Point a, Point b, Point c) {return abs((c - b).cross(c - a));};

int res{}; if (m < 3) {res = (m == 1) ? 0 : dis2(cv[1], cv[0]);} else {
    for (int i = 0, j = 0; i < m; i++) {
        while (area(cv[i], cv[nxt(i)], cv[j]) <= area(cv[i], cv[nxt(i)], cv[nxt(j)])) {j = nxt(j);}
        res = max(res, max(dis2(cv[nxt(i)], cv[j]), dis2(cv[i], cv[j])));
    }
}

//求最小面积矩形覆盖
auto parallelLine = [](Point a, Point b, Point c) {// 求过点a且与b-c平行的直线的方向向量
    Point d = c - b;// 计算方向向量 d = (c - b)
    return make_pair(a, a + d);// 返回与 b-c 平行且经过 a 的直线表示为两个点, 直线的一个点是 a，另一个点是 a + d
};

int T{}, L{}, R{}; {//对0->1这条线初始化L, T, R
    for (int i = 0; i < m; i++) {
        if ((cv[1] - cv[0]).dot(cv[i] - cv[L]) >= 0) {L = i;}//0->1与L->i能形成锐角，就说明i更左
        if ((cv[1] - cv[0]).dot(cv[i] - cv[R]) <= 0) {R = i;}//0->1与R->i能形成钝角，就说明i更右
        if ((cv[1] - cv[0]).cross(cv[i] - cv[T]) >= 0) {T = i;}//0->1与T->i完成了toleft测试，说明更上
    }           
}

double ans{}; PS res(4);
for (int i = 0; i < m; i++) {
    while ((cv[nxt(i)] - cv[i]).dot(cv[nxt(L)] - cv[L]) >= 0) {L = nxt(L);}
    while ((cv[nxt(i)] - cv[i]).dot(cv[nxt(R)] - cv[R]) <= 0) {R = nxt(R);}
    while ((cv[nxt(i)] - cv[i]).cross(cv[nxt(T)] - cv[T]) >= 0) {T = nxt(T);}
    double s{ ((cv[nxt(i)] - cv[i]).dot(cv[L] - cv[R]))
            * ((cv[nxt(i)] - cv[i]).cross(cv[T] - cv[i]))
            / dis2(cv[i], cv[nxt(i)])};
    [&]() {//updata答案，求矩形的四个点
        if (i != 0 and s > ans) {return ;}
        ans = s;
        auto left_down{foot(cv[L], cv[i], cv[nxt(i)])}; auto right_down{foot(cv[R], cv[i], cv[nxt(i)])};//L，R对于cv[i] -> cv[nxt(i)]的垂点
        auto[upa, upb]{parallelLine(cv[T], cv[i], cv[nxt(i)])};//求出过点 T 平行于 cv[i] -> cv[nxt(i)] 的线上的两个点
        auto left_up{foot(cv[L], upa, upb)}; auto right_up{foot(cv[R], upa, upb)};
        res = {left_up, right_up, right_down, left_down};
        return ;
    }();
}

//求凸包最短宽度
using ld = long double;
// a disTo Line b-c
ld disToLine(Point a, Point b, Point c) {
    Point v1 = b - c, v2 = a - c;
    return 1.L * abs(v1.cross(v2)) / sqrtl(v1.dot(v1));
}

void solve()
{
    int n; int testcase{}; while (cin >> n) { if (n == 0) {break ;}
        PS ps(n); for (auto& pi : ps) {cin >> pi;}
        auto cv{convex(ps)}; int m{(int)size(cv)};
        auto area = [&](Point a, Point b, Point c) {return abs((c - b).cross(c - a));};
        auto nxt = [&](int i) {return i == m - 1 ? 0 : i + 1;};
        ld res{numeric_limits<ld>::max()}; if (m < 3) {res = (m == 1) ? 0 : dis2(cv[1], cv[0]);} else {
            for (int i = 0, j = 0; i < m; i++) {
                while (area(cv[i], cv[nxt(i)], cv[j]) <= area(cv[i], cv[nxt(i)], cv[nxt(j)])) {j = nxt(j);}//遍历每一个宽度
                res = min(res, disToLine(cv[j], cv[i], cv[nxt(i)]));//求点到直线的距离
            }
        }
    }
}

template <class T>
pair<T, T> minmaxTriangle(const PS& vec)
{
    int n { (int)(size(vec)) }; if (n <= 2) {return { 0, 0 };}
    
    T maxans = 0, minans = numeric_limits<T>::max(); 

    using pii = pair<int, int>; vector<pii> evt; {//维护线段事件
        evt.reserve(n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) if (i != j) {
                if (vec[i] == vec[j]) { // 有重点，所以可以直接为0
                    minans = 0;
                } else {
                    evt.emplace_back(i, j);
                }
            }
        }
        sort(begin(evt), end(evt), [&](const pii& u, const pii& v) {//对旋转后的向量排极角序
            const Point du = vec[u.second] - vec[u.first], dv = vec[v.second] - vec[v.first];
            return polarCmp<Point>({ du.y, -du.x }, { dv.y, -dv.x });
        });
    }
    
    vector<int> vx(n); {//维护该点在x大小关系中的位置
        iota(begin(vx), end(vx), 0);
        sort(begin(vx), end(vx), [&](int x, int y) { return vec[x] < vec[y]; });
    }

    vector<int> pos(n); {for (int i = 0; i < ssize(vx); i++) {pos[vx[i]] = i;}}//维护索引

    for (auto now : evt) {//按照极角序遍历线段模拟旋转
        auto u = now.first, v = now.second;
        const int i = pos[u], j = pos[v];//找出这个线段左右端点在x轴的大小位置
        const int _i = min(i, j), _j = max(i, j);
        const Point vecu = vec[u], vecv = vec[v];
        if (_i > 0) {//用左最近更新最小答案（左相邻）
            minans = min(minans, abs((vec[vx[_i - 1]] - vecu).cross(vec[vx[_i - 1]] - vecv)));
        }
        if (_j < ssize(vx) - 1) {//用右最近更新最小答案（右相邻）
            minans = min(minans, abs((vec[vx[_j + 1]] - vecu).cross(vec[vx[_j + 1]] - vecv)));
        }
        //用最左或者最右更新最大答案
        maxans = max({ maxans, abs((vec[vx[0]] - vecu).cross(vec[vx[0]] - vecv)), abs((vec[vx.back()] - vecu).cross(vec[vx.back()] - vecv)) });
        if (i < j) {swap(vx[i], vx[j]); pos[u] = j; pos[v] = i;}//旋转后大小关系会交换
    }
    return { minans, maxans };
}