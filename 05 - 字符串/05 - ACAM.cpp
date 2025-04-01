template <int Z, char Base>
struct AcAutomaton {
    std::vector<std::array<int, Z>> trans;
    std::vector<std::vector<int>> ID;
    std::vector<int> fail;
    int SIZE = 0, tot = 0;

    AcAutomaton(const std::vector<std::string> &s) {
        for (auto t : s) {SIZE += t.size();}
        trans.resize(SIZE + 1);
        ID.resize(SIZE + 1);
        fail.resize(SIZE + 1);
        for (int i = 0; i < s.size(); i++) {insert(i, s[i]);}
        build();
    }

    void insert(int id, const std::string &s) {
        int p = 0;
        for (char c : s) {
            c -= Base;
            if (trans[p][c] == 0) {
                trans[p][c] = ++tot;
            }
            p = trans[p][c];
        }
        ID[p].push_back(id);
    }

    void build() {
        std::queue<int> q;
        for (int &y : trans[0]) if (y != 0) {q.push(y);}
        while (not q.empty()) {
            int x = q.front();
            q.pop();
            for (int c = 0; int &y : trans[x]) {
                if (y != 0) {
                    fail[y] = trans[fail[x]][c];
                    q.push(y);
                } else {
                    y = trans[fail[x]][c];
                }
                c++;
            }
        }
    }
};