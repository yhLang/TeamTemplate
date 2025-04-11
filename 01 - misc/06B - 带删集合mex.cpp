class Mex {
    // 数组 count[i] 表示数字 i 出现的次数
    vector<int> count;
    // 使用有序集合存储缺失的数字（即频次为 0 的数字）
    set<int> missing;

public:
    // 值域
    Mex(int n) : count(n) {
        for (int i = 0; i < n; i++) {
            missing.insert(i);
        }
    }

    // 插入一个元素 x（修改操作）
    void insert(int x) {
        count[x] += 1;
        // 若之前没有该元素，则从 missing 中删除
        if (count[x] == 1) {
            missing.erase(x);
        }
    }

    // 删除一个元素 x
    void remove(int x) {
        if (count[x] == 0) {
            // x 不存在，无需处理
            return;
        }
        count[x] -= 1;
        // 若删除后频次变为0，说明 x 变成“缺失”，加入 missing 集合
        if (count[x] == 0) {
            missing.insert(x);
        }
    }

    // 查询当前集合的 mex
    int getMex() {
        // missing 中最小的元素就是当前的 mex
        return *begin(missing);
    }
};