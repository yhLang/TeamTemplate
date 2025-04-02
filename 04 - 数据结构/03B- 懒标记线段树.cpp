inline int __lg(int __n) { return sizeof(int) * __CHAR_BIT__  - 1 - __builtin_clz(__n); }

template<class Info, class Tag>
struct LazySegmentTree {
    const int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree(int n) : n(n), info(4 << __lg(n)), 
    tag(4 << __lg(n)) {}
    LazySegmentTree(vector<Info> init) : 
    LazySegmentTree(init.size()) {
        function<void(int, int, int)> build = 
        [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }

    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        push(p);
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }

    template<class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        push(p);
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, 0, n, l, r, pred);
    }

};

constexpr i64 inf{(i64)1E18};

//基础区间加
struct Tag {
    i64 add{};
    
    void apply(Tag t) {
        add += t.add;
    }
};

struct Info {
    i64 min{inf};
    i64 max{-inf};
    i64 sum{};
    i64 act{1};
    
    void apply(Tag t) {
        min += t.add;
        max += t.add;
        sum += act * t.add;
    }

};

Info operator+(Info a, Info b) {
    Info c;
    c.min = min(a.min, b.min);
    c.max = max(a.max, b.max);
    c.sum = a.sum + b.sum;
    c.act = a.act + b.act;
    return c;
}

//区间加 + 区间乘
struct Tag {
    Z add{}, mul{1};
    void apply(Tag t) {
        add *= t.mul;//先让在该乘法之前的addtag都进行乘法操作
        add += t.add;//
        mul *= t.mul;
    }
};

struct Info {
    Z sum{};
    Z act{1};
    
    void apply(Tag t) {
        sum *= t.mul;//先乘再加，才能保证正确性
        sum += act * t.add;
    }

};

Info operator+(Info a, Info b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.act = a.act + b.act;
    return c;
}

// 区间加，最小值以及最小值个数
struct Tag {
    i64 add{};
    
    void apply(Tag t) {
        add += t.add;
    }
};
 
struct Info {
    i64 min{inf};
    i64 cnt{};
    
    void apply(Tag t) {
        min += t.add;
    }

};

Info operator+(Info a, Info b) {
    if (a.min < b.min) {
        return a;
    } else if (a.min > b.min) {
        return b;
    } else {
        return {a.min, a.cnt + b.cnt};
    }
}

// 扫描线求矩形面积并
// 区间加+维护最小值及最小值个数
struct Tag {
    i64 add{};
    void apply(Tag t) {
        add += t.add;
    }
};

struct Info {
    i64 min_cover{inf<i64>};//cover最小值是多少
    i64 cnt_min_cover{};//这里的cnt是最小值的个数，这里的个数指的是x线（扫描线）的实际点数

    void apply(Tag t) {
        min_cover += t.add;
    }
};

Info operator+(Info a, Info b)
{
    if (a.min_cover < b.min_cover) {
        return a;
    } else if (a.min_cover > b.min_cover) {
        return b;
    } else {
        return Info{a.min_cover, a.cnt_min_cover + b.cnt_min_cover};
    }
}

auto solve()
{
    int n; cin >> n;

    vector<Event> events; vector<int> xs; {
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            xs.push_back(x1); xs.push_back(x2);
            events.emplace_back(y1, 1, x1, x2);
            events.emplace_back(y2, -1, x1, x2);
        }
        sort(begin(events), end(events));
    }

    Discreter<int> disc(xs);//离散化x坐标，用来当线段树下标

    const auto m = disc.size() - 1;
    vector<Info> init(m); i64 tot_cover_x{}; {//初始的每一段x值都是出现0次
        for (int i = 0; i < m; i++) {
            const auto d = disc.queryInv(i + 1) - disc.queryInv(i);
            tot_cover_x += d;
            init[i] = {0, d};
        }
    }
    LazySegmentTree<Info, Tag> seg(init);

    int pre_y{}; i64 ans{};
    for (const auto&[y, opt, x1, x2] : events) {//沿着y轴开始扫，从下往上
        auto cover_x = tot_cover_x;
        if (seg.rangeQuery(0, m).min_cover == 0) {//说明有一些段为0，要减去了
            cover_x -= seg.rangeQuery(0, m).cnt_min_cover;
        }
        ans += 1LL * cover_x * (y - pre_y);//cover_x * cover_y
        seg.rangeApply(disc.query(x1), disc.query(x2), {opt});//更新扫描线上的信息
        pre_y = y;
    }
    
    cout << ans << "\n";

}



