inline int __lg(int __n) { 
    if (__n == 0) {return -1;}
    return sizeof(int) * __CHAR_BIT__  - 1 - __builtin_clz(__n); 
}

template <class T, class Cmp = greater<T>>
struct Max {
    const Cmp cmp = Cmp();
    constexpr T operator()(const T &a, const T &b) const {
        return min(a, b, cmp);
    }
};

template <class T, class Merge = plus<T>>
class Fenwick {
    const int n;
    vector<T> t;
    const Merge merge;
public:
    Fenwick(int n) : n{n}, t(n + 1), merge(Merge()) {}

    // O(n) build Fenwick
    Fenwick(const vector<T> &a) : Fenwick(a.size()) {
        for (int i = 1; i <= n; i++) {
            t[i] = merge(t[i], a[i - 1]);
            int j = i + (i & -i);
            if (j <= n) {
                t[j] = merge(t[j], t[i]);
            }
        }
    }

    void modify(int i, const T &x) {
        for (i += 1; i <= n; i += i & -i) {
            t[i] = merge(t[i], x);
        }
    }

    //[0, i]
    T posQuery(int i) const {
        T res = T{};
        for (i += 1; i > 0; i -= i & -i) {
            res = merge(res, t[i]);
        }
        return res;
    }

    // [l, r)
    // T rangeQuery(int l, int r) {
    //     return posQuery(r - 1) - posQuery(l - 1);
    // }

    // 合并起来 <= k 的最长前缀
    int select(const T &k) const {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i > 0; i /= 2) {
            if (x + i <= n and merge(cur, t[x + i]) <= k) {
                x += i;
                cur = merge(cur, t[x]);
            }
        }
        return x - 1;
    }
};

/*
求逆序对
*/
const auto M = ranges::max(a);
Fenwick<int> bit(M + 1);//posQuery是右闭的！
i64 cnt{}; {
    for (int i = n - 1; i >= 0; i--) {
        // cnt += bit.posQuery(a[i]);// i < j, a[i] >= a[j]
        cnt += bit.posQuery(a[i] - 1);// i < j, a[i] > a[j]
        bit.modify(a[i], 1);
    }
}


/*
离线查询求区间内不同种类元素数目
*/
struct Query {
    int l, r, id;
    bool operator < (const Query &rhs) const {
        return r < rhs.r;
    }
};

class DistinctQuerySolver {
private:
    vector<int> a;       // 原数组
    vector<Query> queries; // 查询序列，查询区间格式 [l, r)，其中 l 为 0-indexed

public:
    DistinctQuerySolver(const vector<int>& a, vector<Query> q)
        : a(a), queries(q)
    {}
    
    // solve() 方法：离线处理所有查询，返回一个按照原始查询顺序排列的答案数组
    vector<int> solve() {
        int n = size(a);
        int q = size(queries);
        
        // 计算数组中元素的最大值，用于构造 lastOccurrence 数组
        const auto M = ranges::max(a) + 1;
        
        // 将查询按照右端点 r 升序排序
        auto sortedQueries = queries;
        sort(begin(sortedQueries), end(sortedQueries));
        
        // 初始化树状数组，大小为 n
        Fenwick<int> fwk(n);
        
        // lastOccurrence 用于记录每个元素最后一次出现的位置，初始均设为 -1（表示未出现）
        vector<int> lastOccurrence(M, -1);
        
        // 用于存储每个查询的答案，按照查询的 id 放置
        vector<int> res(q, 0);
        
        // currentRight 表示当前处理到的右端点
        int currentRight{};
        // 依次处理排序后的每个查询
        for (const auto&[l, r, id] : sortedQueries) {
            // 将 currentRight 移动到查询的右端点 r（区间 [l, r)）
            while (currentRight < r) {
                auto value = a[currentRight];
                // 若该元素之前出现过，则更新之前位置的贡献（计数减 1）
                if (lastOccurrence[value] != -1) {
                    fwk.add(lastOccurrence[value], -1);
                }
                // 更新该元素的最后出现位置为 currentRight
                lastOccurrence[value] = currentRight;
                // 在当前下标位置上加 1
                fwk.add(currentRight, 1);
                currentRight++;
            }
            // 查询区间 [l, r) 内的不同元素个数，即为 fwk 在该区间的和
            res[id] = fwk.rangeSum(l, r);
        }
        
        return res;
    }
};