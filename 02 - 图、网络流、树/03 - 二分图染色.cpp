// 函数功能：对无向图进行二分染色，如果图为二分图则返回每个顶点对应的染色（0或1），否则返回空数组
vector<int> bipartiteVertexColoring(vector<vector<int>>& adj) {
    // 获取顶点总数
    const int n = ssize(adj);

    // 初始化并查集，大小为 2*n
    // 每个顶点有两个身份：
    //  - 下标 [0, n-1] 表示顶点染色为 0 的身份
    //  - 下标 [n, 2*n-1] 表示顶点染色为 1 的身份
    DSU dsu(2 * n);

    // 遍历图中每条边，为保证相邻顶点染色不同，进行如下合并操作：
    for (int u = 0; u < n; u++) {
        for (const auto& v : adj[u]) {
            // 将顶点 u 的1身份（u+n）和顶点 v 的0身份合并，表示若 u 染成1，则 v 必须染成0
            dsu.merge(u + n, v);
            // 将顶点 u 的0身份和顶点 v 的1身份（v+n）合并，表示若 u 染成0，则 v 必须染成1
            dsu.merge(u, v + n);
        }
    }

    // 初始化颜色数组，大小为 2*n，初始值为 -1 表示未分配颜色
    vector<int> color(2 * n, -1);

    // 为每个连通块分配颜色
    // 对于每个顶点 u，如果 u 是所在集合的代表且该集合还未染色，则：
    //  - 将其代表染成颜色 0
    //  - 将对应对立身份（u+n所在集合）染成颜色 1
    for (int u = 0; u < n; ++u) {
        if (dsu.find(u) == u && color[dsu.find(u)] < 0) {
            color[dsu.find(u)] = 0;
            color[dsu.find(u + n)] = 1;
        }
    }

    // 将染色结果映射回原图的顶点
    // 对每个顶点 u，通过找到 u 在并查集中的代表，并将代表的颜色赋给 u
    for (int u = 0; u < n; ++u) {
        color[u] = color[dsu.find(u)];
    }
    // 缩减数组大小，只保留原图顶点的颜色
    color.resize(n);

    // 检查图是否为二分图
    // 如果对于某个顶点 u，其两个身份（u 和 u+n）在并查集中属于同一集合，
    // 则表示 u 同时被要求染成0和1，矛盾出现，图就不是二分图
    for (int u = 0; u < n; ++u) {
        if (dsu.find(u) == dsu.find(u + n)) {
            return {}; // 返回空数组表示无法进行二分染色
        }
    }

    // 返回最终每个顶点的染色结果
    return color;
}