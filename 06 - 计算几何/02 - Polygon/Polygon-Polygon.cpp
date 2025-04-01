PS minkowski(const PS &a, const PS &b) {
    int n = a.size(), m = b.size();
    if (!n or !m)
        return PS();

    PS ps(1, a[0] + b[0]);
    int ap = 0, bp = 0;
    while (ap < n and bp < m) {
        auto va = a[(ap + 1) % n] - a[ap];
        auto vb = b[(bp + 1) % m] - b[bp];
        auto res = va.cross(vb);
        if (res > 0)
            ps.push_back(ps.back() + va), ap++;
        if (res < 0)
            ps.push_back(ps.back() + vb), bp++;
        if (res == 0)
            ps.push_back(ps.back() + va + vb), ap++, bp++;
    }
    while (ap < n) {
        auto va = a[(ap + 1) % n] - a[ap];
        ps.push_back(ps.back() + va), ap++;
    }
    while (bp < m) {
        auto vb = b[(bp + 1) % m] - b[bp];
        ps.push_back(ps.back() + vb), bp++;
    }
    return ps.pop_back(), ps;
}