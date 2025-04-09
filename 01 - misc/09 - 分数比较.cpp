bool cmp(auto& x, auto& y) {
    auto[xa, xb] = x; auto[ya, yb] = y;
    // 负数都归到分子上面,不然会挂,比如
    // 12 / -2 cmp -2 / 12
    // 本来应该是 12 / -2 < -2 / 12
    // 然而 12 * 12 > -2 * -2
    // 而归一化之后
    // -12 / 2 cmp -2 / 12
    // -12 * 12 < 2 * -2
    // 正确  
    if (xb < 0) {xb = -xb; xa = -xa;}
    if (yb < 0) {yb = -yb; ya = -ya;}
    return static_cast<i64>(xa) * yb < static_cast<i64>(xb) * ya;
}