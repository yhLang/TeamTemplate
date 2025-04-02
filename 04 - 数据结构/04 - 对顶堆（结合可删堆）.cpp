template <class T, class Cmp = less<T>>
struct Heap {//可删堆
    priority_queue<T, vector<T>, Cmp> qPush, qErase; // Heap=qPush-qErase
    i64 sum;
 
    Heap() : sum{0} {}
 
    void push(T x) {
        qPush.push(x);
    }
 
    void erase(T x) {
        qErase.push(x);
    }
 
    T top() {
        while (!qErase.empty() && qPush.top() == qErase.top())
            qPush.pop(), qErase.pop();
        return qPush.top();
    }
 
    void pop() {
        while (!qErase.empty() && qPush.top() == qErase.top()) {
            qPush.pop(), qErase.pop();
        }
 
        qPush.pop();
    }
 
    int size() {
        return qPush.size() - qErase.size();
    }
};

template<class T>
struct DualHeap {//结合可删堆，形成可删对顶堆
 
    Heap<T, greater<T>> small; // small root
    Heap<T, less<T>> big;      // big root
    //中位数就是bit.top()
    DualHeap() {}
 
    void update() {
        if (big.size() == 0 and small.size() == 0) {
            return;
        }
 
        while (big.size() > small.size() + 1) {
            T x = big.top();
            big.pop();
            small.push(x);
        }
 
        while (big.size() < small.size()) {
            T x = small.top();
            small.pop();
            big.push(x);
        }
    }
 
    void push(T val) {
        if (big.size() == 0) {
            big.push(val);
            return;
        }
 
        if (val <= big.top()) {
            big.push(val);
        } else {
            small.push(val);
        }
 
        update();
    }
 
    void erase(T val) {
        assert(big.size() >= 1);
 
        if (val <= big.top()) {
            big.erase(val);
        } else {
            small.erase(val);
        }
 
        update();
    }

};