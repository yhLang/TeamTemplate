map<vector<int>, int> id;
vector<vector<int>> sub;
vector<int> siz;
int getid(const vector<int> &T) {
    if (id.contains(T)) return id[T];
    int s = 1;
    for (int x : T) {
        s += siz[x];
    }
    sub.push_back(T);
    siz.push_back(s);
    return id[T] = size(id);
}
int dfs(int u, int fa) {
    vector<int> S;
    for (auto& v : adj[u]) if (v != fa) {
        S.push_back(dfs(v, u));
    }
    ranges::sort(S);
    return getid(S);
}