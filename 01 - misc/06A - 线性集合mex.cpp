{//无视值域，只和数组长度有关，因为 mex 最大也就 0 ~ n - 1 这种情况，也就是 n，所以只考虑 < n 的就行
    vector<int> a(n);
    vector<int> exist(n);
    int mex{};
    for (auto& ai : a) {
        if (ai < n) { exist[ai] += 1; }
        while (mex < n and exist[mex]) ++mex;
    }
}