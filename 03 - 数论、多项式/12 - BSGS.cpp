i64 BSGS(i64 a, i64 b, i64 p)
{
    if (1 % p == b % p) { // a^0 mod p = b mod p
        return 0; // 特判x = 0，1%p是因为p可能等于1
    }
    unordered_map<i64, i64> hash;
    i64 k = sqrt(p) + 1;
    for (i64 B = 0, val = b % p; B < k; B++) { // 构造哈希表/map，b * (a^B)  ->  B
        hash[val] = B;
        val = val * a % p; // b * (a^B)，每次乘以一个a
    }
    i64 ak = 1; // 预处理 a^k
    for (i64 i = 0; i < k; i++) {
        ak = ak * a % p;
    }

    for (i64 A = 1, val = ak; A <= k; A++) { // val = (a ^ k) ^ A
        if (hash.contains(val)) {
            return A * k - hash[val]; // A*k - B
        }
        val = val * ak % p;
    }
    return -1; // 无解
}