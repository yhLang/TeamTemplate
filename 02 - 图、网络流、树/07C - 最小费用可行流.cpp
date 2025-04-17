// 最小费用可行流
template <class T, class F>
class MCFGraphOK {
    MCFGraph<T, F> flow;
    int superStr;
    T totCap;
public:
    MCFGraphOK(int n) : flow(n + 1), superStr{n}, totCap{} {}
    void add(int x, int y, T cap, F fees) {
        flow.add(x, y, cap, fees);
        totCap += cap;
    }
    std::pair<T, F> work(int s, int t) {
        flow.add(superStr, s, totCap, 0);
        flow.add(s, t, totCap, 0);
        return flow.work(superStr, t);
    }
};