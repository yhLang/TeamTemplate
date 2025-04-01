template <class T, class G>
class Dijkstra {
    const vector<vector<pair<int, T>>> &e;
    vector<vector<G>> dis;

    auto get(int s) {
        vector<G> dis(e.size(), numeric_limits<G>::max() / 2);

        using pii = pair<G, int>;
        priority_queue<pii, vector<pii>, greater<>> q;

        dis[s] = G();
        q.push({dis[s], s});

        while (!q.empty()) {
            auto [D, x] = q.top();
            q.pop();

            if (D > dis[x])
                continue;

            for (auto &&[y, w] : e[x]) {
                if (dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    q.push({dis[y], y});
                }
            }
        }
        return dis;
    }

public:
    Dijkstra(const vector<vector<pair<int, T>>> &g)
        : e(g), dis(g.size()) {}

    G operator()(int x, int y) {
        if (dis[x].empty())
            dis[x] = get(x);
        return dis[x][y];
    }
};