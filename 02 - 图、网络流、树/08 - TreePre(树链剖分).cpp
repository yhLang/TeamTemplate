template <class T>
class TreePre {
    static constexpr int endPoint(int x) {
        return x;
    }
    template <class G>
    static constexpr int endPoint(const pair<int, G> &pr) {
        return pr.first;
    }

    void dfs1(int x, int f) {
        fa[x] = f;

        for (auto p : adj[x]) {
            int y = endPoint(p);
            if (y != f) {
                dep[y] = dep[x] + 1;
                dfs1(y, x);

                size[x] += size[y];
                if (big[x] == -1 or size[y] > size[big[x]]) {
                    big[x] = y;
                }
            }
        }
    }
    void dfs2(int x, int top) {
        dfn[x] = cur++;
        idfn[dfn[x]] = x;
        tp[x] = top;
        if (big[x] != -1) {
            dfs2(big[x], top);
        }

        for (auto p : adj[x]) {
            int y = endPoint(p);
            if (y != big[x] and y != fa[x]) {
                dfs2(y, y);
            }
        }
    }
    const vector<vector<T>> &adj;

    const int n;
    const int root;

public:
    vector<int> size, big, dep, tp, fa, dfn, idfn;
    // dfn begin from 0
    int cur = 0;

    TreePre(const vector<vector<T>> &g, int root)
        : adj(g), n{g.size()}, root{root}, big(n, -1), size(n, 1),
          tp(n), dep(n), fa(n), dfn(n), idfn(n) {
        // dep begin from 0
        // dep[root] = 0;
        dfs1(root, -1);
        dfs2(root, root);
    }

    int getLca(int x, int y) {
        while (tp[x] != tp[y]) {
            if (dep[tp[x]] > dep[tp[y]]) {
                x = fa[tp[x]];
            } else {
                y = fa[tp[y]];
            }
        }
        return (dep[x] < dep[y] ? x : y);
    }

    int dist(int x, int y) {
        int lca = getLca(x, y);
        return dep[x] + dep[y] - 2 * dep[lca];
    }

    // x→y路径剖分的dfn号区间[l, r], l > r 说明这是上升段
    auto getRoad(int x, int y) {
        int lca = getLca(x, y);
        vector<pair<int, int>> vec1, vec2;
        while (tp[x] != tp[lca]) {
            vec1.push_back({dfn[x], dfn[tp[x]]});
            x = fa[tp[x]];
        }

        if (x != lca) {
            vec1.push_back({dfn[x], dfn[lca] + 1});
        }

        vec1.push_back({dfn[lca], dfn[lca]});

        while (tp[y] != tp[lca]) {
            vec2.push_back({dfn[tp[y]], dfn[y]});
            y = fa[tp[y]];
        }

        if (y != lca) {
            vec2.push_back({dfn[lca] + 1, dfn[y]});
            y = fa[tp[y]];
        }

        vec1.insert(vec1.end(), vec2.rbegin(), vec2.rend());
        return vec1;
    }

    int kthAncester(int x, int k) {
        if (dep[x] - dep[root] < k) {
            return -1;
        }

        int d = dep[x] - k;

        while (dep[tp[x]] > d) {
            x = fa[tp[x]];
        }

        return idfn[dfn[x] - dep[x] + d];
    }

    // x is y's ancester
    bool isAncester(int x, int y) {
        return dfn[x] <= dfn[y] and dfn[y] < dfn[x] + size[x];
    }
};