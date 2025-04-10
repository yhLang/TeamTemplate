#ifdef LOCAL
inline constexpr int __lg(int __n) { return sizeof(int) * __CHAR_BIT__  - 1 - __builtin_clz(__n); }
#endif
