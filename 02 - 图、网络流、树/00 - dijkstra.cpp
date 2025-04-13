template <class T, class G>
class Dijkstra {
    const vector<vector<pair<int, T>>> &e;
    vector<vector<G>> dis;

    auto get(int s) {
        vector<G> dis(size(e), numeric_limits<G>::max() / 2);

        using pii = pair<G, int>;
        priority_queue<pii, vector<pii>, greater<>> q;

        dis[s] = G();
        q.push({dis[s], s});

        while (not empty(q)) {
            auto [D, x] = q.top();
            q.pop();

            if (D > dis[x])
                continue;

            for (auto and[y, w] : e[x]) {
                if (dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    q.emplace(dis[y], y);
                }
            }
        }
        return dis;
    }

public:
    Dijkstra(const vector<vector<pair<int, T>>> &g)
        : e(g), dis(size(g)) {}

    G operator()(int x, int y) {
        if (empty(dis[x]))
            dis[x] = get(x);
        return dis[x][y];
    }
};