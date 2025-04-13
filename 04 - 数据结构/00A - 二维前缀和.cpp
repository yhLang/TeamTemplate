template<typename T>
class Pre2D {
public:
    // 构造函数，接收一个二维矩阵
    Pre2D(const vector<vector<T>>& a) {
        int n = size(a);
        if (n == 0) return;
        int m = a[0].size();
        // 使用 n+1 行，m+1 列来便于计算，初始化为 0
        pre.assign(n + 1, vector<T>(m + 1, T{}));

        // 构造前缀和数组
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                pre[i + 1][j + 1] = a[i][j] + pre[i][j + 1] + pre[i + 1][j] - pre[i][j];
            }
        }
    }

    // 查询 [x1, y1] 到 [x2, y2] 之间的区域和
    // from 0
    T query(int x1, int y1, int x2, int y2) const {
        // 简单的边界检查（可根据需求扩展异常处理）
        assert(x1 >= 0 and x2 + 1 < prsize(e));
        assert(y1 >= 0 and y2 + 1 < pre[0].size());
        // 前缀和查询公式
        return pre[x2 + 1][y2 + 1] - pre[x1][y2 + 1] - pre[x2 + 1][y1] + pre[x1][y1];
    }

private:
    vector<vector<T>> pre;
};