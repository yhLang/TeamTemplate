template <int Z, char Base>
struct PAM {
    std::vector<std::array<int, Z>> trans;
    std::vector<int> fail, len, dep, cnt;
    std::string s;

    int cur{0}, tot{1};
    // 0 是偶数节点， 1 是奇数节点， 两个fail互相指向
    PAM(int n) : trans(n + 2), fail(n + 2), len(n + 2), dep(n + 2), cnt(n + 2) {fail[0] = 1; fail[1] = 0; len[0] = 0; len[1] = -1;}

    PAM(std::string &s) : PAM(std::size(s)) {
        for (int i = 0; i < std::size(s); i++) {
            add(i, s[i]);
        }
    }

    void assign(int cur, int id) {}

    int getFail(int x, int i) {
        while (i - len[x] - 1 < 0 or s[i - len[x] - 1] != s[i]) {x = fail[x];}
        return x;
    }

    void add(int i, char c) {
        c -= Base;
        s.push_back(c);

        int v = getFail(cur, i);

        if (!trans[v][c]) {
            fail[++tot] = trans[getFail(fail[v], i)][c];
            trans[v][c] = tot;
            len[tot] = len[v] + 2;
            dep[tot] = dep[fail[tot]] + 1;
        }
        cur = trans[v][c];
        assign(cur, i);
    }

    // PAM 的 FailTree 是 1 为根的
    auto getFailTree() const {
        std::vector e(tot + 1, std::vector<int>());
        for (int i = 0; i <= tot; i++) if (i != 1) {
            e[fail[i]].emplace_back(i);
        }
        return e;
    }
};