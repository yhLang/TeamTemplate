#include <bits/stdc++.h>

using namespace std;

template <class F, class S>
ostream& operator<<(ostream& s, const pair<F, S>& v)
{
    return s << "(" << v.first << ", " << v.second << ")";
}
template <ranges::range T>
    requires(!is_convertible_v<T, string_view>)
istream& operator>>(istream& s, T&& v)
{
    for (auto&& x : v)
        s >> x;
    return s;
}
template <ranges::range T>
    requires(!is_convertible_v<T, string_view>)
ostream& operator<<(ostream& s, T&& v)
{
    for (auto&& x : v)
        s << x << ' ';
    return s;
}

#ifdef LOCAL
template <class... T>
void dbg(T... x)
{
    char e {};
    ((cerr << e << x, e = ' '), ...);
}
#define debug(x...) dbg(#x, '=', x, '\n')
#else
#define debug(...) ((void)0)
#endif

template <class T>
inline constexpr T inf = numeric_limits<T>::max() / 2;
template <class T>
bool chmin(T& a, T b) { return (b < a) and (a = b, true); }
template <class T>
bool chmax(T& a, T b) { return (b > a) and (a = b, true); }

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;

signed main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    auto solve = [&]() {
        srand(time(0));
        
    };

    int t{1};

    while (t--) {
        solve();
    }

    return 0;
}
