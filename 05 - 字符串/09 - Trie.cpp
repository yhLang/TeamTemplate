// 字典树节点模板类，模板参数 D 表示字符集大小，例如 26 代表小写英文字母
template <int D>
struct TrieNode {
    array<TrieNode*, D> son; // 子节点数组，大小为 D，每个元素指向对应字符的子节点
    int cnt;  // 当前节点作为字符串结尾的次数
    int size; // 以当前节点为前缀的字符串数量
    TrieNode(int val = 0) : cnt{val}, size{0}, son{} {} // 构造函数初始化 cnt、size，并将子节点数组初始化为空
};

// 将 TrieNode 固定为字符集大小 26 的字典树节点类型，适用于小写英文字母
using Node = TrieNode<26>;

// 字典树封装类
class Trie {
public:
    Trie() {
        root = new Node{};
    }
    
    ~Trie() {
        clear(root);
    }
    
    // 向字典树插入字符串
    void insert(string_view s) {
        Node *p = root;      // 从根节点开始插入
        p->size += 1;        // 根节点表示所有字符串的前缀，更新前缀字符串数量

        for (char c : s) {   // 遍历字符串中的每个字符
            int idx = c - 'a'; // 将字符转换为索引，范围为 [0, 25]
            if (p->son[idx] == nullptr) { // 如果对应索引的子节点不存在，则创建新节点
                p->son[idx] = new Node{};
            }
            p = p->son[idx]; // 移动到子节点
            p->size += 1;    // 更新当前节点的前缀字符串数量
        }
        p->cnt += 1;         // 更新最后一个节点的 cnt，表示该字符串出现次数增加
    }
    
    // 查询字符串是否存在，返回该字符串出现次数（若返回 0 则表示字符串不存在）
    int search(string_view s) const {
        Node *p = root;
        for (char c : s) {
            int idx = c - 'a';
            if (p->son[idx] == nullptr) {
                return 0;  // 字符串不存在
            }
            p = p->son[idx];
        }
        return p->cnt;
    }
    
    // 查询以指定前缀开头的字符串数量
    int query(string_view prefix) const {
        Node *p = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (p->son[idx] == nullptr) {
                return 0;  // 前缀不存在
            }
            p = p->son[idx];
        }
        return p->size;
    }
    
private:
    Node *root;
    
    // 递归释放字典树所有节点，防止内存泄漏
    void clear(Node *node) {
        if (node == nullptr)
            return;
        for (auto child : node->son) {
            if (child != nullptr)
                clear(child);
        }
        delete node;
    }
};

/*
简化版
*/
struct Node {
    array<Node *, 26> son;
    Node *father;
    Node *link;
    int id;

    Node() : son{}, father{nullptr}, id{-1}, link{nullptr} {
    }
};

void insert(Node *root, string_view s, int id) {
    auto p = root;
    for (char c : s) {
        c -= 'a';
        if (p->son[c] == nullptr) {
            p->son[c] = new Node();
            p->son[c]->father = p;
        }

        p = p->son[c];
    }
    p->id = id;
}

/*
01trie
*/
struct Node {
    array<Node *, 2> son;
    int id;

    Node() : son{}, id{-1} {}
};

constexpr int M{30};

void insert(Node *root, int x, int id) {
    auto p = root;
    for (int i = M; i >= 0; i--) {
        auto c = (x >> i & 1);
		if (p->son[c] == nullptr) {
			p->son[c] = new Node();
		}
		p = p->son[c];
	}
    p->id = id;
}

int getMinXor(Node *root, int x) {
	auto p = root;
	for (int i = M; i >= 0; i--) {
		auto c = (x >> i & 1);
		if (p->son[c]) {p = p->son[c];}//优先走该位置上一样的，这样可以尽可能的碰掉1
        else {p = p->son[c ^ 1];}//实在不行再走不一样的
	}
	return p->id;
}

int getMaxXor(Node *root, int x) {
	auto p = root;
	for (int i = M; i >= 0; i--) {
		auto c = (x >> i & 1);
		if (p->son[c ^ 1]) {p = p->son[c ^ 1];}//优先走该位置上不一样的，这样可以尽可能的保留1
        else {p = p->son[c];}//实在不行再走一样的
	}
	return p->id;
}