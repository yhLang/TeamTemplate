i64 BSGS(i64 a, i64 b, i64 m)
{
    i64 cur{1};
    const i64 K{sqrt(m) + 1};
    unordered_map<i64, i64> hs;
    for (int B = 1; B <= K; ++B)
    {
        (cur *= a) %= m;
        hs[b * cur % m] = B; // 哈希表中存B的值
    }
    i64 now = cur; // 此时cur = a^K
    for (int A = 1; A <= K; ++A)
    {
        if (hs.contains(now)) {
            return A * K - hs[now];
        }
        (now *= cur) %= m;
    }
    return -1; // 没有找到，无解
}