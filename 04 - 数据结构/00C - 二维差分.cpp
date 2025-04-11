template<typename T>
class Diff2D {
    Diff2D(int _n, int _m) : n(_n), m(_m) {
        d.resize(n + 1, vector<T>(m + 1));  // 多加一行一列用于边界处理
    }

    // 执行二维差分加法：给区域 (x1, y1) 到 (x2, y2) 加上 val
    void add(int x1, int y1, int x2, int y2, T val) {
        d[x1][y1] += val;
        if (x2 + 1 < n) d[x2 + 1][y1] -= val;
        if (y2 + 1 < m) d[x1][y2 + 1] -= val;
        if (x2 + 1 < n and y2 + 1 < m) d[x2 + 1][y2 + 1] += val;
    }

    auto get() {// 计算二维差分数组恢复的原数组
        vector res(n, vector<T>(m, 0));

        // 从差分数组恢复原始数组
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i > 0) d[i][j] += d[i - 1][j];
                if (j > 0) d[i][j] += d[i][j - 1];
                if (i > 0 and j > 0) d[i][j] -= d[i - 1][j - 1];

                res[i][j] = d[i][j];
            }
        }

        return res;
    }
    
private:
    vector<vector<T>> d;  // 差分数组
    int n, m;
};