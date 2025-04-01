class TwoSat
{
    const int n;                     // 变量的数量
    vector<vector<int>> adj; // 邻接表，用来存储蕴含图

public:
    vector<bool> ans; // 存储每个变量的最终赋值

    // 构造函数
    // 参数 n 表示布尔变量的数量，构造一个包含 2n 个顶点的蕴含图
    TwoSat(int n) : n(n), adj(2 * n) {}

    // x * 2         为 x 设 0
    // x * 2 + 1     为 x 设 1

    void addClause(int u, bool f, int v, bool g) { // (u = f) or (v = g)
        // (not f -> g)
        // (not g -> f)
        u *= 2; v *= 2;
        adj[u + !f].push_back(v + g);
        adj[v + !g].push_back(u + f);
    }
    void addImply(int u, bool f, int v, bool g) { // (u = f) -> (v = g)
        // (not g -> not f)
        // (f -> g)
        u *= 2; v *= 2;
        adj[u + f].push_back(v + g);
        adj[v + !g].push_back(u + !f);
    }

    // work 函数用于解决 2-SAT 问题
    // 它通过对蕴含图进行强连通分量（SCC）分解来判断是否有解
    // 如果存在解，返回 true 并填充 ans 数组；否则返回 false
    bool work()
    {
        // 使用 SCC 类对蕴含图进行强连通分量分解
        SCC scc(adj);
        const auto &bel = scc.bel; // bel 数组记录每个顶点属于哪个强连通分量
        ans.assign(n, false);      // 初始化答案数组为 false

        // 遍历每个变量
        for (int i = 0; i < n; i++)
        {
            // 如果一个变量 x_i 的 false 和 true 顶点属于同一个强连通分量
            // 则说明无法为该变量赋值，因为它同时为真和为假是不可满足的
            if (bel[2 * i] == bel[2 * i + 1])
                return false; // 如果存在矛盾，返回 false

            // 否则，根据 SCC 的拓扑排序顺序来确定变量的赋值
            // 如果 2*i 对应的 false 顶点在拓扑排序中位于 2*i+1 对应的 true 顶点后面，
            // 则说明 x_i 应该为 false，否则为 true
            ans[i] = bel[2 * i] > bel[2 * i + 1];
        }
        return true; // 如果没有矛盾，返回 true，表示有解
    }
};
