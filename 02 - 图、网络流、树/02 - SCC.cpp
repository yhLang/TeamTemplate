class SCC {
    // ----------------- 私有成员 -----------------
    // e: 原图的邻接表引用，每个节点对应一个整型向量，表示从该节点出发的边
    const vector<vector<int>> &e;
    
    // stk: 辅助栈，用于在 Tarjan 算法中存储当前递归路径上的节点
    vector<int> stk;
    
    // r: 栈顶指针（初始为 0，使用时递增/递减模拟栈操作）
    // cur: 全局计数器，用于给每个节点分配访问顺序编号（dfn值）
    int r = 0, cur = 0;

    // dfs 函数：对节点 x 进行深度优先搜索，计算 dfn 和 low 值，并划分 SCC
    void dfs(int x) {
        // 为节点 x 分配访问编号，并将其 low 值初始化为该编号
        dfn[x] = low[x] = cur++;
        
        // 将节点 x 压入栈中，注意这里先自增栈顶指针，再赋值
        stk[++r] = x;

        // 遍历 x 的所有出边（所有邻接节点 y）
        for (int y : e[x]) {
            if (dfn[y] == -1) {
                // 如果节点 y 还未被访问，则递归调用 dfs(y)
                dfs(y);
                // 递归返回后，更新 x 的 low 值为 x 自身 low 与 y 的 low 中的较小值
                low[x] = min(low[x], low[y]);
            } else if (bel[y] == -1) {
                // 如果 y 已经被访问过但还未分配到某个 SCC 中（即 y 还在栈中）
                // 更新 x 的 low 值为 x 自身 low 与 y 的 dfn 中的较小值
                low[x] = min(low[x], dfn[y]);
            }
        }

        // 如果 x 的 dfn 与 low 相等，说明 x 是一个 SCC 的根节点
        if (dfn[x] == low[x]) {
            int y;
            // 从栈中弹出节点，直到遇到 x 为止，这些节点构成一个 SCC
            do {
                y = stk[r--];       // 弹出栈顶节点
                bel[y] = cntBlock;    // 将节点 y 标记为当前 SCC（编号为 cntBlock）
            } while (y != x);
            // 完成一个 SCC 的划分，SCC 数量计数器递增
            cntBlock += 1;
        }
    }

public:
    // ----------------- 公共成员 -----------------
    // dfn: 存储每个节点在 DFS 中被访问的次序编号（发现时间），初始为 -1 表示未访问
    vector<int> dfn;
    // low: 对于每个节点，记录其能追溯到的最早（最小）访问编号
    vector<int> low;
    // bel: 记录每个节点所属的 SCC 的编号，初始为 -1 表示尚未分配
    vector<int> bel;

    // g: 缩点后的图（DAG），每个节点代表一个 SCC，边表示原图中不同 SCC 之间的连通关系
    vector<vector<int>> g;
    // cntBlock: 记录当前找到的 SCC 数量，同时也作为 SCC 的编号分配器
    int cntBlock = 0;

    // 构造函数：输入原图的邻接表 e，初始化各数据结构并执行 SCC 划分
    SCC(const vector<vector<int>> &e)
        : e(e), dfn(e.size(), -1), low(e.size()), bel(e.size(), -1) {
        int n = e.size();
        
        // 初始化辅助栈的大小（这里分配 n+1 个空间，确保栈操作不会越界）
        stk.resize(n + 1, 0);

        // 对每个节点执行 DFS，如果节点未被访问（dfn == -1），则开始递归搜索
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }

        // 构造缩点后的图：
        // g 的每个节点代表一个 SCC，因此大小为 cntBlock
        g.resize(cntBlock);
        // 遍历原图中的每一条边，根据所属的 SCC 构造缩点图的边
        for (int x = 0; x < n; x++) {
            for (int y : e[x]) {
                // 如果 x 和 y 属于同一个 SCC，则不在缩点图中建立边
                if (bel[x] == bel[y])
                    continue;
                // 否则，在缩点图中添加一条从 SCC bel[x] 到 SCC bel[y] 的边
                g[bel[x]].push_back(bel[y]);
            }
        }

        // 以下代码用于去除缩点图中可能出现的重复边，
        // 如果需要保证缩点图中每条边唯一，可以取消下面注释
        /*
        for (int x = 0; x < cntBlock; x++) {
            sort(begin(g[x]), end(g[x]));
            g[x].erase(unique(begin(g[x]), end(g[x])), end(g[x]));
        }
        */
    }
};
