// 枚举每个分段，l 表示分段的起始位置
for (int l = 0, r; l < n; l = r + 1) {
    r = l;
    // 只要满足扩展条件，就将 r 后移
    while (r + 1 < n and shouldExtend(r + 1)) {
        r++;
    }
    // 处理当前段 [l, r]
    processSegment(l, r);
}