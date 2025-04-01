template <class T, class F>
class MCFGraph {
    // 定义边的结构体，保存目标点、剩余容量和费用
    struct Edge {
        int y;   // 边的目标点
        T c;     // 剩余容量
        F f;     // 单位流量费用
    };

    // 使用Dijkstra算法在带费用的残量网络中寻找最短路径
    bool dijkstra(int s, int t) {
        // 初始化距离数组和前驱数组
        dis.assign(n, numeric_limits<F>::max()); // 最短距离，初始为无穷大
        pre.assign(n, -1);                       // 前驱边编号
        using pii = pair<F, int>;
        priority_queue<pii, vector<pii>, greater<>> q; // 最小优先队列

        dis[s] = 0; // 源点的距离为0
        q.emplace(0, s); // 把源点加入队列

        while (!q.empty()) {
            auto [D, x] = q.top(); // 取出当前距离最小的点
            q.pop();

            if (dis[x] < D) // 如果该点已被松弛过，跳过
                continue;

            // 遍历从当前点出发的所有边
            for (int i : g[x]) {
                const auto& [y, c, f] = adj[i]; // 目标点、剩余容量、费用
                if (c > 0 && dis[y] > D + h[x] - h[y] + f) {
                    // 如果容量大于0且找到更短的路径
                    dis[y] = D + h[x] - h[y] + f; // 更新最短距离
                    pre[y] = i; // 更新前驱边
                    q.emplace(dis[y], y); // 将目标点加入队列
                }
            }
        }
        // 如果汇点的距离仍为无穷大，则无法到达汇点
        return dis[t] != numeric_limits<F>::max();
    }

public:
    const int n; // 图的节点数
    vector<Edge> adj; // 保存所有边的数组
    vector<std::vector<int>> g; // 邻接表，每个节点保存出边的编号
    vector<F> h, dis; // h: 节点的势，dis: 最短路径距离
    vector<int> pre; // 保存每个节点的前驱边

    // 构造函数，初始化图的节点数和邻接表
    MCFGraph(int n) : n(n), g(n) {}

    // 添加一条边，x -> y，容量为c，单位费用为f
    void add(int x, int y, T c, F f) {
        g[x].push_back(adj.size()); // 从x出发的边编号
        adj.emplace_back(Edge{y, c, f}); // 正向边
        g[y].push_back(adj.size()); // 从y出发的反向边编号
        adj.emplace_back(Edge{x, 0, -f}); // 反向边，容量为0，费用为负
    }

    // 求解最小费用最大流
    pair<T, F> work(int s, int t) {
        T flow = 0; // 最大流
        F cost = 0; // 最小费用
        h.assign(n, 0); // 初始化节点的势

        // 不断寻找增广路
        while (dijkstra(s, t)) {
            // 更新势值
            for (int i = 0; i < n; ++i)
                h[i] += dis[i];

            // 找到增广路径上的最小残量
            T aug = numeric_limits<T>::max();
            for (int i = t; i != s; i = adj[pre[i] ^ 1].y)
                aug = min(aug, adj[pre[i]].c);

            // 沿增广路径更新残量网络
            for (int i = t; i != s; i = adj[pre[i] ^ 1].y) {
                adj[pre[i]].c -= aug; // 正向边减去流量
                adj[pre[i] ^ 1].c += aug; // 反向边增加流量
            }

            flow += aug; // 更新总流量
            cost += F(aug) * h[t]; // 更新总费用
        }

        // 返回最大流和对应的最小费用
        return {flow, cost};
    }
};