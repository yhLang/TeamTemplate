// 获取 a 的第 b 位，返回值为 0 或 1
template<typename T>
int getBit(T a, unsigned b) {
    return (a >> b) & static_cast<T>(1);
}

// 将 a 的第 b 位设置为 0
template<typename T>
T unsetBit(T a, unsigned b) {
    return a & ~(static_cast<T>(1) << b);
}

// 将 a 的第 b 位设置为 1
template<typename T>
T setBit(T a, unsigned b) {
    return a | (static_cast<T>(1) << b);
}

// 将 a 的第 b 位取反
template<typename T>
T flipBit(T a, unsigned b) {
    return a ^ (static_cast<T>(1) << b);
}

// <bit> 头文件内置函数

// 1. popcount : 计算二进制中 1 的个数
popcount((unsigned)a);

// 2. countl_zero : 统计数字前导 0 的个数 (对无符号类型)
countl_zero((unsigned)a);

// 3. countr_zero : 统计数字尾部 0 的个数 (对无符号类型)
countr_zero((unsigned)a);

// 4. bit_width : 数字所需的最小二进制位数（a 为 0 时返回 0）
bit_width((unsigned)a);

// 5. has_single_bit : 判断是否只有一个 1（是否为 2 的幂）
has_single_bit((unsigned)a);

// 6. rotl : 位循环左移（此处向左旋转 2 位）
rotl(a, 2);

// 7. rotr : 位循环右移（此处向右旋转 2 位）
rotr(a, 2);

// 8. bit_floor : 返回不超过 a 的最大 2 的幂
// 示例：对于 a = 42，其最大 2 的幂为 32
bit_floor((unsigned)a);

// 10. bit_ceil : 返回不小于 a 的最小 2 的幂
// 示例：对于 a = 42，其最小 2 的幂为 64
bit_ceil((unsigned)a);

