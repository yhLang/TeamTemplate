template <class T>
class Permutation {//会包括第一个排列的
private:
    T a;
    vector<int> idx;
    bool has_next;

public:
    // 构造函数，接受一个容器作为输入
    Permutation(const T& init) : a(init), has_next(true), idx(size(init)) {
        iota(begin(idx), end(idx), 0);        
    }

    // 检查是否还有下一个排列
    bool hasNext() const {return has_next;}

    // 获取当前排列对应的原数组元素
    T next() {
        assert(has_next);

        T res; for (auto& i : idx) {res.push_back(a[i]);}

        // 生成下一个排列
        has_next = next_permutation(begin(idx), end(idx));
        
        return res;
    }
};

int main() 
{
    vector<int> a = {1, 2, 3, 4};
    Permutation processor(a);
    
    while (processor.hasNext()) {
        auto a = processor.next();
        
        for (const auto& ai : a) {
            cout << ai << " ";
        }
        cout << endl;
    }
    
    return 0;
}