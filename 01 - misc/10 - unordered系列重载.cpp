constexpr u64 RATIO = 0x9e3779b97f4a7c15ULL;

template<typename... T>
inline void hashMerge(size_t& seed, const T&... args) {
    // fold 表达式将每个 args 的哈希值混合到 seed 中
    ((seed ^= hash<T>{}(args) + RATIO + (seed << 6) + (seed >> 2)), ...);
}

// 1. pair 与 tuple 的哈希函数

// pair 的哈希函数，利用 hashMerge 处理两个元素
struct HashPair {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        size_t seed = 0;
        hashMerge(seed, p.first, p.second);
        return seed;
    }
};

// tuple 的哈希函数，通过 apply 展开所有元素，再调用 hashMerge
struct HashTuple {
    template <typename... T>
    size_t operator()(const tuple<T...>& t) const {
        size_t seed = 0;
        apply([&seed](const T&... args) {
            hashMerge(seed, args...);
        }, t);
        return seed;
    }
};

// 2. 自定义结构体 AC 与哈希函数

struct AC {
    string x, y;
    int z;

    bool operator==(const AC &other) const {//自定义什么是相等
        return x == other.x && y == other.y && z == other.z;
    }
};

struct HashAC {
    size_t operator()(const AC &p) const {
        size_t seed = 0;
        hashMerge(seed, p.x, p.y, p.z);
        return seed;
    }
};

// 3. 模板化的 vector 哈希函数

template <typename T>
struct HashVector {
    size_t operator()(const vector<T>& a) const {
        size_t seed = a.size();  // 使用 vector 大小作为初始值
        for (const auto &ai : a) {
            hashMerge(seed, ai);
        }
        return seed;
    }
};