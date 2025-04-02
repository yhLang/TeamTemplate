using i128 = __int128;

ostream &operator<<(ostream &os, i128 n) {
    string s;
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}