struct Manacher {
    // n 为原字符串 t 的长度
    const int n;
    // r 数组：存储每个位置的回文半径（扩展后的字符串中对应位置的回文半径）
    // f 数组：维护以某位置为“尾部”（回文串结尾）的最长回文半径
    // g 数组：维护以某位置为“开头”（回文串开头）的最长回文半径
    vector<int> r, f, g;
    
    // 构造函数，传入原字符串 t
    Manacher(const string &t)
        : n(t.size()), r(2 * t.size() + 3), f(2 * t.size() + 3), g(2 * t.size() + 3) {
        // 将原字符串 t 转换成处理后的字符串 s，增加分隔符 '-' 和边界符 "[-"、"]"
        // 这样做的目的是统一处理奇偶回文串问题，避免区分奇数回文与偶数回文
        string s = "[-";
        for (int i = 0; i < n; i++) {
            s.push_back(t[i]);
            s.push_back('-');
        }
        s.push_back(']');

        // mid 表示当前回文串的中心位置，far 表示当前回文串能延伸到的最右边界
        int mid = 1, far = 1;
        // 遍历处理后的字符串 s，每个位置 i 求解回文半径 r[i]
        for (int i = 1; i < s.size(); i++) {
            // 利用已知的回文信息，对称位置为 2*mid-i，初始半径取 min(r[2*mid-i], far-i)
            r[i] = min(r[2 * mid - i], far - i);
            // 尝试扩展回文：只要两侧字符相等，就可以扩展半径
            while (s[i + r[i]] == s[i - r[i]]) {
                r[i] += 1;
            }
            // 更新当前最右回文串的信息
            if (i + r[i] > far) {
                mid = i;
                far = i + r[i];
            }
            // f 数组维护以某位置为尾部的最长回文串
            // i + r[i] - 1 为回文串在 s 中的尾部位置
            // 更新 f 数组为该位置最大回文半径
            f[i + r[i] - 1] = max(f[i + r[i] - 1], r[i]);
            // g 数组维护以某位置为开头的最长回文串
            // i - r[i] + 1 为回文串在 s 中的起始位置
            g[i - r[i] + 1] = max(g[i - r[i] + 1], r[i]);
        }
        // f 数组向前传递：确保 f[i] 表示以 i 为尾部的最长回文串，
        // 当往前一个位置时，回文半径可能减1，因此 f[i] = max(f[i], f[i+1]-1)
        for (int i = s.size() - 2; i > 0; i--) {
            f[i] = max(f[i], f[i + 1] - 1);
        }
        // g 数组向后传递：确保 g[i] 表示以 i 为开头的最长回文串，
        // 当往后一个位置时，回文半径可能减1，因此 g[i] = max(g[i], g[i-1]-1)
        for (int i = 1; i < s.size(); i++) {
            g[i] = max(g[i], g[i - 1] - 1);
        }
    }

    // 函数：返回以位置 i 为中心（若 center 为 false，则代表奇数回文；为 true，则代表以 i 和 i+1 为中心的偶数回文）的回文串长度
    // 解释：转换到 s 中的位置为 2*(i+1) + center，因为 s 中有边界符和分隔符的影响，所以需要映射
    int getPalinLenFromCenter(int i, int center) const {
        // 断言判断：当 center 为 false，i 必须在 [0, n) 内；当 center 为 true，i 必须在 [0, n-1) 内
        assert((!center && 0 <= i && i < n) || (center && 0 <= i && i < n - 1));
        // 返回的回文串长度为 r 值减 1
        return r[2 * (i + 1) + center] - 1;
    }

    // 函数：返回以位置 i 为尾部的最长回文串的长度
    // 在 s 中，原串 t 中位置 i 对应 s 中的位置为 2*(i+1)
    int getPalinLenFromTail(int i) const {
        assert(0 <= i && i < n);
        return f[2 * (i + 1)];
    }

    // 新增函数：返回以位置 i 为开头的最长回文串的长度
    // 类似 getPalinLenFromTail，这里利用 g 数组得到信息
    int getPalinLenFromHead(int i) const {
        assert(0 <= i && i < n);
        return g[2 * (i + 1)];
    }
};
