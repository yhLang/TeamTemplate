// 自定义floor函数：计算“商”（向下取整除法运算）
// 对于两个数a和b，通常的整数除法a / b在舍入规则上可能存在问题，尤其是负数的情况。
// 这里的实现确保当余数不为0，并且a与b符号相反时，需要向下修正商（减1）。
template <typename T>
T floor(T a, T b) {
    // a / b 本身是向零舍入的除法结果（即在C/C++中，当a为负数时向上舍入）。
    // (a % b) 返回除法运算的余数，当余数不为0且(a ^ b) < 0时，即a和b符号不同，说明需要往下调整1。
    // (a ^ b) 的结果为负表示a和b一个正，一个负。&&逻辑运算确保只有有余数时才需要调整。
    return a / b - (a % b && (a ^ b) < 0);
}

// 自定义ceil函数：计算“上取整”除法运算
// ceil(x, y)计算的是不小于 x / y 的最小整数。
// 此实现通过将x调整后再调用floor函数计算得到。
template <typename T>
T ceil(T x, T y) {
    // 当 x + y - 1 的时候，通过floor函数得到的商就是上取整的结果。
    return floor(x + y - 1, y);
}

// 自定义bmod函数：计算非负模（余数）运算
// 这个函数保证了模运算结果总是非负的，这在某些数学应用中非常有用。
template <typename T>
T bmod(T x, T y) {
    // 计算x与y的非负余数。公式为：x - y * floor(x, y)
    return x - y * floor(x, y);
}

// 自定义divmod函数：同时返回商和余数
// 此函数返回一个pair，其中第一个元素为向下取整的商，第二个元素为对应的余数（由 x - q*y 计算）。
template <typename T>
pair<T, T> divmod(T x, T y) {
    // 计算商q，此处使用之前定义的floor函数
    T q = floor(x, y);
    // 余数是x减去q乘以y的结果，即 x - q*y
    return {q, x - q * y};
}