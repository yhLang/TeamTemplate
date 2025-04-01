class LCA {
    using Adj = std::vector<std::vector<int>>;  
public:
    int m_num;                              
    int m_lognum;                            
    int m_root;                              
    std::vector<std::vector<int>> m_parent;  
    std::vector<int> m_depth;                
 
    LCA(const Adj& g, int root) {
        init(g, root);
    }
 
    void init(const Adj& g, int root) {
        m_num = static_cast<int>(g.size());
        m_root = root;
 
        m_lognum = 1;
        while (m_num >> m_lognum) ++m_lognum;
 
        m_parent.assign(m_lognum, std::vector<int>(m_num, -1));
        m_depth.assign(m_num, -1);
        dfs(g, m_root, -1, 0);
        for (int k = 0; k + 1 < m_lognum; k++) {
            for (int i = 0; i < m_num; i++) {
                if (m_parent[k][i] != -1)
                    m_parent[k + 1][i] = m_parent[k][m_parent[k][i]];
            }
        }
    }
 
    void dfs(const Adj& g, int v, int p, int d) {
        m_parent[0][v] = p;
        m_depth[v] = d;
        for (const auto& to : g[v]) {
            if (to != p) dfs(g, to, v, d + 1);
        }
    }
 
    int lca(int u, int v) {
        if (m_depth[u] > m_depth[v]) std::swap(u, v);
 
        for (int k = 0; k < m_lognum; k++) {
            if ((m_depth[v] - m_depth[u]) >> k & 1) {
                v = m_parent[k][v];
            }
        }
 
        if (u == v) return u;
 
        for (int k = m_lognum - 1; k >= 0; k--) {
            if (m_parent[k][u] != m_parent[k][v]) {
                u = m_parent[k][u];
                v = m_parent[k][v];
            }
        }
        return m_parent[0][u];
    }
};