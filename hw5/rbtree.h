#include <iostream>

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int key;
    Color color;
    Node *left, *right, *parent;
    Node(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree
{
public:
    int rotateCount;
    RedBlackTree() : root(nullptr),rotateCount(0) {}
    /* 插入 key（注意这里没有额外判断 key 是否已经存在，默认不存在）*/
    ~RedBlackTree()
    {
        clear(root);
    }
    void insert(const int &key)
    {
        //insert
        Node *node = new Node(key);
        if (!root)
        {
            root = node;
            root->color = BLACK; // 根节点必须为黑色
            return;
        }
        Node *parent = findParent(root, key); // 找到合适的父节点
        if (key < parent->key)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }
        node->parent = parent;
        fixInsertion(node);
    }
    /* 从节点 node 开始中遍历打印红黑树 */
    void inOrderTraversal(Node *node)
    {
        if (node)
        {
            inOrderTraversal(node->left);
            std::cout << (node->color == RED? "R":"B");
            std::cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }
    /* 从根节点开始遍历打印红黑树 */
    void inOrderTraversal()
    {
        inOrderTraversal(root);
    }
    int getHight(Node *node)
    {
        if (!node)  return 0;
        return std::max(getHight(node->left), getHight(node->right)) + 1;
    }
    int search(const int &key)
    {
        Node *node = findNode(root, key);
        if (node)
            return node->key;
        return -1;
    }

private:
    Node *root;
    void clear(Node *node)
    {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }
    }

    /* 查找键为 key 的节点 */
    Node *findNode(Node *node, const int &key)
    {
        /* TODO: 查找结点 */
        if(!node)
            return nullptr;
        if(node->key == key)
            return node;
        if(key < node->key)
            return findNode(node->left, key);
        else
            return findNode(node->right, key);
    }
    /* 找到键 key 合适的父节点（仅插入时使用）*/
    // 类似BST
    Node *findParent(Node *node, const int &key)
    {
        if (key < node->key) {
            if (!node->left)
                return node;
            return findParent(node->left, key);
        }
        else {
            if (!node->right)
                return node;
            return findParent(node->right, key);
        }
    }
    /* 循环向上解决双红情况 */
    void fixInsertion(Node *node)
    {
        while (node != root && node->parent->color == RED)
        {
            if (node->parent == node->parent->parent->left) {
                Node *uncle = node->parent->parent->right;
                /* TODO: 根据叔父节点的颜色选择不同的处理方法 */
                /* NOTE: 注意局部解决后改变 node 的值以继续循环向上 */
                if(uncle && uncle->color == RED)
                {  /*       黑          红
                *          / \         / \
                *          红 红  -->  黑  黑
                *         / \        / \
                *        红         红
                */
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent; // fix parent->parent
                }
                else {
                    if(node == node->parent->right) {
                    /*          黑          黑
                    *          / \         / \
                    *         红1  黑 --> 红2  黑
                    *          \         / \
                    *          红2      红1
                    */
                        node = node->parent;
                        rotateLeft(node);
                    }

                    /*          黑          黑
                    *          / \         / \
                    *        红1  黑 -->  红2   红
                    *        /                  \
                    *       红2                  黑
                    */

                    node->parent->color = BLACK; // 红1变黑，变root
                    node->parent->parent->color = RED; //原root变红
                    rotateRight(node->parent->parent);
                    break;
                }
            }
            else {
                Node *uncle = node->parent->parent->left;
                /* TODO: 根据叔父节点的颜色选择不同的处理方法 */
                /* NOTE: 注意局部解决后改变 node 的值以继续循环向上 */
                if(uncle && uncle->color == RED)
                {  /*       黑          红
                *          / \         / \
                *          红 红  -->  黑  黑
                *              \           \
                *               红          红
                */
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent; // fix parent->parent
                }
                else {
                    if(node == node->parent->left) {
                        /*          黑          黑
                        *          / \         / \
                        *        黑   红1 -->  黑  红2
                        *            /              \
                        *          红2               红1
                        */
                        node = node->parent;
                        rotateRight(node);
                    }
                    /*          黑          黑（红2）
                    *          / \         / \
                    *         黑  红2 -->  红  红1
                    *              \      /
                    *              红1   黑
                    */
                    node->parent->color = BLACK; // 红2变黑，变root
                    node->parent->parent->color = RED; //原root变红
                    rotateLeft(node->parent->parent);
                    break;
                }
            }
        }
        /* 循环到根节点仍然存在双红，则树的高度 +1 */
        if (node == root && node->color == RED )
            root->color = BLACK;

    }
    /* 左旋 */
    void rotateLeft(Node *node)
    {
        rotateCount++;
        Node *rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left)
        {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (!node->parent)
        {
            root = rightChild;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = rightChild;
        }
        else
        {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }
    /* 右旋 */
    void rotateRight(Node *node)
    {
        rotateCount++;
        Node *leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right)
        {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (!node->parent)
        {
            root = leftChild;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = leftChild;
        }
        else
        {
            node->parent->left = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }
};