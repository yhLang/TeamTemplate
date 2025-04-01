struct HLD {
    int n;                              // 节点总数
    vector<int> siz;               // siz[u]：以 u 为根的子树的大小（节点个数）
    vector<int> top;               // top[u]：节点 u 所在重链的链头
    vector<int> dep;               // dep[u]：节点 u 的深度（根的深度为 0）
    vector<int> parent;            // parent[u]：节点 u 的父亲节点（根节点的 parent 为 -1）
    vector<int> in;                // in[u]：节点 u 在 DFS 序中的进入时间/序号
    vector<int> out;               // out[u]：节点 u 在 DFS 序中的退出时间（区间为 [in[u], out[u])）
    vector<int> seq;               // seq[i]：DFS 序中第 i 个节点对应的节点编号
    vector<vector<int>> adj;  // 邻接表，存储树的无向边（后续会去掉父亲以便 DFS 遍历）
    int cur;                            // DFS 序计数器，用于给 in/out 序号赋值

    // 默认构造函数
    HLD() {}

    // 构造函数：初始化 n 个节点
    HLD(int n) {
        init(n);
    }

    // 初始化函数，分配各个数组空间并重置 DFS 计数器
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        // 初始化邻接表，每个节点对应一个空的 vector
        adj.assign(n, {});
    }

    // 添加一条无向边，连接节点 u 和 v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 主流程函数，从 root 开始构造重链剖分（默认 root = 0）
    void work(int root = 0) {
        top[root] = root;      // 根节点所在链的链头就是其自身
        dep[root] = 0;         // 根的深度为 0
        parent[root] = -1;     // 根没有父节点，用 -1 表示
        dfs1(root);            // 第一次 DFS：计算子树大小，调整子节点顺序（重儿子排第一）
        dfs2(root);            // 第二次 DFS：确定每个节点的 DFS 序号 in、out 和所在链的 top
    }

    // dfs1 用于计算每个节点的子树大小，并确定重儿子（子树大小最大的那个）
    void dfs1(int u) {
        // 若 u 不是根节点，则将父节点从 u 的邻接表中移除，
        // 避免后续遍历时回到父节点（树是无向的）
        if (parent[u] != -1) {
            // erase 返回被删除元素的位置，这里直接删除找到的父亲
            adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;  // 初始化 u 的子树大小（至少包括 u 自己）
        // 遍历 u 的所有子节点 v（此时 adj[u] 中不包含父节点）
        for (auto &v : adj[u]) {
            parent[v] = u;         // 设置 v 的父节点为 u
            dep[v] = dep[u] + 1;     // v 的深度比 u 深 1
            dfs1(v);               // 递归处理 v 的子树
            siz[u] += siz[v];      // 累加 v 的子树大小
            // 保证第一个子节点为重儿子：如果当前 v 的子树大小大于 adj[u][0] 对应子树的大小，则交换
            if (siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    }

    // dfs2 用于确定 DFS 序、in/out 数组和每个节点所属链的链头
    void dfs2(int u) {
        in[u] = cur++;         // 为 u 赋予 DFS 序号，并递增计数器
        seq[in[u]] = u;        // 记录 DFS 序列：序号 in[u] 对应的节点为 u
        // 遍历 u 的所有子节点（注意此时已排好序，重儿子在首位）
        for (auto v : adj[u]) {
            // 如果 v 是 u 的重儿子，则 v 继承 u 所在链的链头，即 top[v] = top[u]；
            // 否则 v 自己成为新链的链头，即 top[v] = v
            top[v] = (v == adj[u][0] ? top[u] : v);
            dfs2(v);         // 递归处理 v
        }
        out[u] = cur;        // u 的子树 DFS 序结束时的计数值，即 [in[u], out[u]) 为 u 的子树区间
    }

    // 求两个节点 u 和 v 的最近公共祖先（LCA）
    int lca(int u, int v) {
        // 当 u 和 v 不在同一条重链上时，将较深那条链上的节点上跳到该链的父链
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        // 当 u 和 v 在同一条链上时，深度较小的那个即为 LCA
        return dep[u] < dep[v] ? u : v;
    }
    
    // 求两个节点 u 和 v 的距离（边数）
    int dist(int u, int v) {
        // 两点距离 = dep[u] + dep[v] - 2 * dep[lca(u, v)]
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    // jump(u, k)：从节点 u 出发向上跳 k 步（也可以理解为到深度为 dep[u]-k 的节点）
    // 如果 u 的深度小于 k，则返回 -1 表示跳不到
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        
        int d = dep[u] - k;    // 目标节点应具有的深度
        
        // 当 u 所在重链的链头深度大于目标深度时，说明目标节点不在当前链，
        // 则 u 跳到该链的父链中
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        
        // 此时 u 所在链已经包含目标深度的节点，
        // 利用 DFS 序 in[]，可以计算出目标节点的位置：
        // 当前 u 在 DFS 序中的位置为 in[u]，u 的深度为 dep[u]，目标深度为 d，
        // 因此目标节点的 DFS 序号为 in[u] - (dep[u] - d)；
        // seq 数组中存储 DFS 序对应的节点
        return seq[in[u] - dep[u] + d];
    }
    
    // 判断 u 是否为 v 的祖先（包括 u 本身）
    bool isAncester(int u, int v) {
        // 利用 DFS 序性质：u 是 v 的祖先当且仅当 in[u] <= in[v] < out[u]
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    // rootedParent(u, v)：
    // 在以某个节点为根的树中，假设 u 和 v 在同一棵树上，
    // 返回 u 在 v 方向（v 为 u 的子树）上的那个儿子，即 u 的 v 子树中与 u 相邻的那个节点
    int rootedParent(int u, int v) {
        // 交换 u 和 v，使得 u 表示 v 的父节点方向（因为题目中调用时会交换）
        swap(u, v);
        if (u == v) {
            return u; // 如果相等则直接返回 u
        }
        // 如果 u 不是 v 的祖先，则 u 与 v 不在同一条路径上，
        // 那么 u 的父节点即为答案
        if (!isAncester(u, v)) {
            return parent[u];
        }
        // 否则，在 u 的子节点中查找 v 所在的子树
        // 利用 upper_bound 按 DFS 序查找，第一个大于 v 的子节点，
        // 然后退一步即为答案
        auto it = upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    // rootedSize(u, v)：
    // 在以某个节点为根的树中，求 v 为根的子树中排除 u 后的大小，
    // 或者在 u 不在 v 的子树中时直接返回 v 的子树大小
    int rootedSize(int u, int v) {
        if (u == v) {
            return n; // 如果 u 和 v 相等，则整个树的大小为 n
        }
        if (!isAncester(v, u)) {
            return siz[v]; // 如果 v 不是 u 的祖先，则直接返回 v 的子树大小
        }
        // 否则，u 在 v 的子树中，
        // 结果为整个树大小减去 u 在 v 方向的那棵子树的大小
        return n - siz[rootedParent(u, v)];
    }
    
    // rootedLca(a, b, c)：
    // 求三个节点 a, b, c 在以某个节点为根的树中的 LCA，
    // 利用异或的性质：lca(a,b) ^ lca(b,c) ^ lca(c,a) 得到答案
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
