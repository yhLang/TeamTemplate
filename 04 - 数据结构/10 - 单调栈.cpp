//Cmp是要把怎样的元素pop掉，比如 greater 就是把大于他的pop掉，greater_equal就是大于等于他的pop掉
//greater 系列栈底到栈顶单调递增，能找到第一个小于的，一开始push极小值
//less 系列栈底到到栈顶单调递减，能找到第一个大于的，一开始push极大值

template <class T, class Cmp = greater_equal<T>> // >= 
class MonotonyStack
    : private stack<pair<T, int>, vector<pair<T, int>>> {//注意vector这里是三个>
    static constexpr Cmp cmp = Cmp();

public:
    MonotonyStack(const T &val, int id) {//一开始要放入的极限元素，保证栈始终非空且保持单调性
        this->emplace(val, id);
    }

    int push(const T &val, int id) {
        while (this->empty() == false and cmp(this->top().first, val)) {
            this->pop();
        }

        assert(this->empty() == false);
        int result = this->top().second;

        this->emplace(val, id);

        return result;
    }
};

//求每一个数的下一个更大数的下标。
void solve()
{
    int n; cin >> n;
    vector<int> a(n); for (auto& ai : a) {cin >> ai;}
    MonotonyStack<int, less_equal<int>> monostack(inf<int>, -1);
    vector<int> res(n);
    for (int i = n - 1; i >= 0; i--) {
        res[i] = monostack.push(a[i], i);
    }
}