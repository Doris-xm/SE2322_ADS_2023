#include <algorithm>
#include <cstdint>
#include <stack>
#include <cstdio>
#include <cassert>
#include <string>
static inline uint64_t rdtsc()
{
    uint32_t low, high;
    asm volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t)high << 32) | low;
}

class RandGenerator {
private:
    uint64_t seed = 0;
    constexpr static int32_t BASE = 1103515245;
    constexpr static int32_t OFFSET = 12345;
    constexpr static int32_t MOD = 1e9 + 7;

public:
    uint32_t treap_rand() {
        seed = (BASE * seed + OFFSET) % MOD;
        return seed;
    }

    void reset() {
        seed = 0;
    }
};

template<typename T>
class Treap;

template<typename T>
class TreapNode {

private:
    T val;
    TreapNode<T> *left;
    TreapNode<T> *right;
    int32_t count; /* number of repeated elements contained in current node */
    int32_t size; /* number of nodes in current subtree */
    uint32_t weight;
    friend class Treap<T>;

public:
    TreapNode() : val(T()), left(nullptr), right(nullptr), count(0), size(1), weight(0) {}

    TreapNode(T val,TreapNode *left, TreapNode *right,
              int32_t count, int32_t size, uint32_t weight) :
            val(val), left(left), right(right),
            count(count), size(size), weight(weight) {}
};

template<typename T>
class Treap {
public:
    int total_split_times = 0;
    int total_merge_times = 0;
    int total_update_times = 0;
    int split_num = 0;
    int merge_num = 0;
    int update_num = 0;

    int32_t get_height() {
        return treap_root ? get_height(treap_root) : 0;
    }
    int32_t get_size() {
        return treap_root ? treap_root->size : 0;
    }


private:

    int32_t get_height(TreapNode<T> *node) {
        if (!node) return 0;
        return std::max(get_height(node->left), get_height(node->right)) + 1;
    }
    RandGenerator rand;

    TreapNode<T> *treap_root = nullptr;

    int update_size(TreapNode<T> *node) {
        if (!node) return 0;
        node->size = node->count + 1;
        if (node->left) {
            int tmp = update_size(node->left);
            node->size += tmp;
        }
        if (node->right) node->size += update_size(node->right);
        return node->size;
    }

    void split(T val, TreapNode<T>* curr, TreapNode<T>** leftRoot, TreapNode<T>** rightRoot) {
        if( !curr) { //如果当前节点为空
            *leftRoot = *rightRoot = nullptr; //左右子树都为空
            return;
        }
        if( val < curr->val) { //如果当前节点的值大于val
            //这里把当前的结点作为右子树的根节点
            // 然后右子树的根节点递归到curr->left（因为右侧必然大于val，连枝放进rightRoot）
            split(val, curr->left, leftRoot, &curr->left);
            *rightRoot = curr;
        } else {
            split(val, curr->right, &curr->right, rightRoot);
            *leftRoot = curr;
        }
//        curr->size = curr->count + 1;
//        curr->size += (curr->left ? curr->left->size : 0);
//        curr->size += (curr->right ? curr->right->size : 0);

    }

    void merge(TreapNode<T>* leftRoot, TreapNode<T>* rightRoot, TreapNode<T>** root) {
        //合并时要保持最大堆的性质
        if( !leftRoot) {
            *root = rightRoot;
            return;
        }
        if( !rightRoot) {
            *root = leftRoot;
            return;
        }
        if( leftRoot->weight < rightRoot->weight) {
            //rightRoot成为新的root
            // 有三段：leftRoot, rightRoot->right，rightRoot->left
            //BST性质：leftRoot与rightRoot->left合并，放到rightRoot的左子树
            merge(leftRoot, rightRoot->left, &rightRoot->left);
            *root = rightRoot; //weight大的作为root
//            (*root)->size = (*root)->count + 1;
//            (*root)->size += ((*root)->left ? (*root)->left->size : 0);
//            (*root)->size += ((*root)->right ? (*root)->right->size : 0);
        } else {
            merge(leftRoot->right, rightRoot, &leftRoot->right);
            *root = leftRoot;
//            (*root)->size = (*root)->count + 1;
//            (*root)->size += ((*root)->left ? (*root)->left->size : 0);
//            (*root)->size += ((*root)->right ? (*root)->right->size : 0);
        }
    }


    void clear(TreapNode<T>* node) {
        if( !node ) return;
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }

    void pre_traverse(TreapNode<T>* node, std::string *str) {
        if( !node ) return;
        char s = ' ';
        *str = (*str) + std::to_string(node->val);
        *str = (*str) + s;
        pre_traverse(node->left,str);
        pre_traverse(node->right,str);
    }

    int32_t kth_element(TreapNode<T>* tmp, int32_t rk) { //输出排名为k的元素
        /* Your code here. */
        if(!treap_root) return -1;
        if(rk > treap_root->size || rk <= 0) return -1;
        int left_size = 0;
        if(tmp->left) left_size = tmp->left->size;
        while(left_size != rk - 1) {
            if(left_size > rk - 1) { //左子树结点太多，往左走
                tmp = tmp->left;
                left_size = tmp->left ? tmp->left->size : 0;
                continue;
            }
            if(left_size < rk - 1) {
                rk -= left_size;
                if (rk <= (tmp->count + 1)) return tmp->val;
                rk -= (tmp->count + 1);
                tmp = tmp->right;
                left_size = tmp->left ? tmp->left->size : 0;
            }
        }
        return tmp->val;
    }


public:
    void insert(T val) {
        /* Your code here. */
        TreapNode<T>* left, *right;
        //按照val将整棵树分成左右两部分。其中左⼦树的值全部⼩于等于val，右⼦树的值全部严格⼤于val。
        int64_t start, end;

        start = rdtsc();
        split(val, treap_root,&left, &right);
        end = rdtsc();
        total_split_times += (end - start);
        split_num++;

        //在左⼦树中查找是否已经存在val的节点，假设存在则增加其counter，结束插⼊操作
        TreapNode<T> *tmp = left;
        while(tmp) {
            if(tmp->val == val) {
                tmp->count++;
                break;
            }
            tmp = tmp->right;//左子树的值都比val小
        }
        if(tmp) {
            //如果存在，那么就把左右子树合并
            start = rdtsc();
            merge(left, right, &treap_root);
            end = rdtsc();
            total_merge_times += (end - start);
            merge_num++;

            start = rdtsc();
            update_size(treap_root);
            end = rdtsc();
            total_update_times += (end - start);
            update_num++;
            return;
        }

        //如果不存在，那么就新建一个节点
        TreapNode<T> *newNode = new TreapNode<T>(val, nullptr, nullptr, 0, 1, rand.treap_rand());
        //把val节点和左⼦树合并成⼀颗新的左⼦树,再把新的左⼦树和右⼦树合并
        TreapNode<T> *temp = nullptr;
        start = rdtsc();
        merge(left, newNode, &temp);
        merge(temp, right, &treap_root);
        end = rdtsc();
        total_merge_times += (end - start);
        merge_num += 2;

        start = rdtsc();
        update_size(treap_root);
        end = rdtsc();
        total_update_times += (end - start);
        update_num++;
    }

    void remove(T val) {
        /* Your code here. */
        TreapNode<T>* left, *right,*subLeft, *subRight;
        //按val分成左右
        int64_t start, end;
        start = rdtsc();
        split(val, treap_root, &left, &right);

        //将左⼦树划分为⼩于val的subLeft和等于val的subRight
        split(val-1, left, &subLeft, &subRight);
        end = rdtsc();
        total_split_times += (end - start);
        split_num += 2;

        //如果sub右⼦树存在则count--，如果减少到0则删除sub右⼦树。
        if(subRight) {
            if(subRight->count == 0) {
                delete subRight;
                subRight = nullptr;
            }
            else
                subRight->count--;
        }
        //将subLeft和subRight合并，再将合并后的subLeft和right合并
        if(subRight) {
            TreapNode<T> *temp = nullptr;
            start = rdtsc();
            merge(subLeft, subRight, &temp);
            merge(temp, right, &treap_root);
            end = rdtsc();
            total_merge_times += (end - start);
            merge_num += 2;
        }
        else {
            start = rdtsc();
            merge(subLeft, right, &treap_root);
            end = rdtsc();
            total_merge_times += (end - start);
            merge_num++;
        }
        start = rdtsc();
        update_size(treap_root);
        end = rdtsc();
        total_update_times += (end - start);
        update_num++;

    }

    T pre_element(T val) { //输出前驱元素
        /* Your code here. */
        TreapNode<T>* left(nullptr), *right(nullptr);
        int64_t start, end;
        start = rdtsc();
        split(val-1, treap_root, &left, &right);
        end = rdtsc();
        total_split_times += (end - start);
        split_num ++;

        if( !left ) return -1;

        start = rdtsc();
        update_size(left);
        end = rdtsc();
        total_update_times += (end - start);
        update_num ++;
        int res = kth_element(left, left->size);
        start = rdtsc();
        merge(left, right, &treap_root);
        end = rdtsc();
        total_merge_times += (end - start);
        merge_num ++;

        start = rdtsc();
        update_size(treap_root);
        end = rdtsc();
        total_update_times += (end - start);
        update_num ++;
        return res;
    }

    T suc_element(T val) { //输出后继元素
        /* Your code here. */
        TreapNode<T>* left(nullptr), *right(nullptr);
        int64_t start, end;
        start = rdtsc();
        split(val, treap_root, &left, &right);
        end = rdtsc();
        total_split_times += (end - start);
        split_num ++;

        start = rdtsc();
        update_size(right);
        end = rdtsc();
        total_update_times += (end - start);
        update_num ++;

        int res = kth_element(right, 1);
        start = rdtsc();
        merge(left, right, &treap_root);
        end = rdtsc();
        total_merge_times += (end - start);
        merge_num ++;

        start = rdtsc();
        update_size(treap_root);
        end = rdtsc();
        total_update_times += (end - start);
        update_num ++;
        return res;
    }

    int32_t rank(T val) { //输出排名
        /* Your code here. */
        TreapNode<T>* left(nullptr), *right(nullptr);
        int64_t start, end;
        start = rdtsc();
        split(val-1, treap_root, &left, &right); //严格小于val都在left
        end = rdtsc();
        total_split_times += (end - start);
        split_num ++;

        if (!left) return 1;

        start = rdtsc();
        update_size(left);
        end = rdtsc();
        total_update_times += (end - start);
        update_num ++;

        int res = left->size + 1;
        start = rdtsc();
        merge(left, right, &treap_root);
        end = rdtsc();
        total_merge_times += (end - start);
        merge_num ++;

        start = rdtsc();
        update_size(treap_root);
        end = rdtsc();
        total_update_times += (end - start);
        update_num ++;
        return res;
    }

    int32_t kth_element(int32_t rk) { //输出排名为k的元素
        /* Your code here. */
        return kth_element(treap_root, rk);
    }

    void clear() {
        /* Your code here. */
        clear(treap_root);
        treap_root = nullptr;
        rand.reset();
    }

    std::string pre_traverse() { //前序遍历
        /* Your code here. */
        if (!treap_root) return std::string("empty");
        std::string res = "";
        pre_traverse(treap_root, &res);
        return res;
    }
};
