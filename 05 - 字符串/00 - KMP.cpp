void getBorder(const string& s)
{
    int m = s.size();
    vector<int> border(m + 1);
    //border[i]表示字符串s[0, i - 1]的后缀与前缀的最长非平凡border（后缀与前缀均不包含字符串本身）
    border[0] = 0;
    border[1] = 0;
    for (int i = 1; i < m; ++i) {
        int j = border[i];
        while (j and s[j] != s[i]) {j = border[j];}
        border[i + 1] = s[j] == s[i] ? j + 1 : 0;
    }
}

void find(const string& s, const string& t)
{
    int n = s.size(), m = t.size();
    const auto border = getBorder(t);
    int j {};
    for (int i = 0; i < n; ++i) {
        while (j and t[j] != s[i]) {
            j = border[j];
        }
        if (t[j] == s[i]) {
            ++j;
        }
        if (j == m) {
            cout << i - m + 1 << '\n';//输出当前找到的，from0
            j = border[j];//继续往下找
        }
    }
}
