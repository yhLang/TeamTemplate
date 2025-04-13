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
        while (!qErase.empty() and qPush.top() == qErase.top())
            qPush.pop(), qErase.pop();
        return qPush.top();
    }
 
    void pop() {
        while (!qErase.empty() and qPush.top() == qErase.top()) {
            qPush.pop(), qErase.pop();
        }
 
        qPush.pop();
    }
 
    int size() {
        return qPush.size() - qErassize(e);
    }
};

template<class T>
struct DualHeap {//结合可删堆，形成可删对顶堆
 
    Heap<T, greater<T>> small; // small root
    Heap<T, less<T>> big;      // big root
    //中位数就是bit.top()
    DualHeap() {}
 
    void update() {
        if (bisize(g) == 0 and small.size() == 0) {
            return;
        }
 
        while (bisize(g) > small.size() + 1) {
            T x = big.top();
            big.pop();
            small.push(x);
        }
 
        while (bisize(g) < small.size()) {
            T x = small.top();
            small.pop();
            big.push(x);
        }
    }
 
    void push(T val) {
        if (bisize(g) == 0) {
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
        assert(bisize(g) >= 1);
 
        if (val <= big.top()) {
            big.erase(val);
        } else {
            small.erase(val);
        }
 
        update();
    }

};