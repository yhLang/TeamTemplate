class EdgeBC {
    const vector<vector<int>> &e;//存原来的无向图
    vector<int> stk; // stack
    int r = 0, cur = 0;

    void dfs(int x, int fa) {//dfs生成树上跑强连通分量
        dfn[x] = low[x] = cur++;
        stk[++r] = x;//把本次递归到的所有节点（也就是该联通快所有节点）压栈

        for (int y : e[x]) {
            if (y == fa) {//如果邻接节点 y 是当前节点的父节点，则跳过（将 fa 反转的目的是为了避免将父节点自身当作回边处理）。
                fa = ~fa;
                continue;
            }
          //强连通分量
            if (dfn[y] == -1) {
                dfs(y, x);
                low[x] = min(low[x], low[y]);
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
                
        if (dfn[x] == low[x]) {//符合强连通分量条件，这个联通块内点集就是一个边双联通分量
            int y;
            do {
                y = stk[r--];
                bel[y] = cntBlock;//bel[y](y结点对应的联通快编号)
            } while (y != x);
            cntBlock += 1;
        }
    }

public:
    // original graph
    vector<int> dfn, low, bel;//bel[y](y结点对应的联通快编号)
    // shrinking graph
    vector<vector<int>> g;//由桥构成的无根树
    int cntBlock = 0, componentNum = 0;

    EdgeBC(const vector<vector<int>> &e)
        : e(e), dfn(e.size(), -1), low(e.size()), bel(e.size(), -1), cutDeg(e.size()) {
        int n = e.size();
        q.assign(n + 1, 0);

        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                componentNum += 1;
                dfs(i, -1);
            }
        }

        g.resize(cntBlock);
        for (int x = 0; x < n; x++) {
            for (int y : e[x]) {
                if (bel[x] == bel[y])
                    continue;
                //否则就是桥
                g[bel[x]].push_back(bel[y]);
            }
        }
    }
};