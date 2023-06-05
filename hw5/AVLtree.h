#pragma once

using namespace std;

template <typename T>
class node_avl{
public:
    T key;
    int height;
    node_avl * left;
    node_avl * right;
    node_avl(T k){
        height = 1;
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class AVL{
public:
    int rotateCount;
    node_avl<T> * root;
//        int num;

    AVL(){root = nullptr;rotateCount = 0;}
    void insert(T x){
        insertUtil(root, x);
    }

    void remove(T x){
        root = removeUtil(root, x);
    }

    node_avl<T> * search(T x){
        return searchUtil(root,x);
    }

    void inorder(){
        inorderUtil(root);
    }
private:
    int height(node_avl<T> * head){
        if(head == nullptr) return 0;
        return head->height;
    }

    node_avl<T> * rightRotation(node_avl<T> * head){
        rotateCount++;
        node_avl<T> * newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node_avl<T> * leftRotation(node_avl<T> * head){
        rotateCount++;
        node_avl<T> * newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    // Traverse and print AVL tree
    void inorderUtil(node_avl<T> * head){
        if(head==nullptr) return ;
        inorderUtil(head->left);
        inorderUtil(head->right);
    }

    void insertUtil(node_avl<T> * &head,const T &x){
        // TODO: finish insertUtil
        if(head == nullptr)
            head = new node_avl<T>(x);
        else if(x < head->key) {
            insertUtil(head->left, x);
            if(height(head->left) - height(head->right) == 2) {
                if(x < head->left->key) head = rightRotation(head);
                else  {
                    head->left = leftRotation(head->left);
                    head = rightRotation(head);
                }
            }
        }
        else if(x >= head->key) {
            insertUtil(head->right, x);
            if(height(head->right) - height(head->left) == 2) {
                if(x >= head->right->key) head = leftRotation(head);
                else  {
                    head->right = rightRotation(head->right);
                    head = leftRotation(head);
                }
            }
        }
        head->height = max(height(head->left), height(head->right)) + 1;
    }

    bool adjust(node_avl<T> *&t, int subTree) {
        if(subTree){
            if(height(t->left)-height(t->right) == 1)return true;
            if(height(t->right) == height(t->left)){
                --t->height; return false;
            }
            if(height(t->left->right) > height(t->left->left)){
                t->left = leftRotation(t->left);
                t = rightRotation(t);
                return false;
            }
            t = rightRotation(t);
            if(height(t->right) == height(t->left)) return false;
            else return true;
        }
        else{
            if(height(t->right)- height(t->left) == 1) return true;
            if(height(t->right) == height(t->left)){
                --t->height; return false;
            }
            if(height(t->left->right) > height(t->left->left)){
                t->right = rightRotation(t->right);
                t = leftRotation(t);
                return false;
            }
            t = leftRotation(t);
            if(height(t->right) == height(t->left)) return false;
            else return true;
        }
    }

    bool removeUtil(node_avl<T> * head,const T &x){
        // TODO: finish removeUtil
        if(head == nullptr) return true;
        if(x == head->key) {
            if(!head->left || !head->right) {
                node_avl<T> *old = head;
                head = (head->left)? head->left : head->right;
                delete old;
                return false;
            }
            else {
                node_avl<T>* tmp = head->right;
                while(tmp->left) tmp = tmp->left;//find right son's smallest son
                head->key = tmp->key;
                if(removeUtil(head->right,tmp->key)) return true;
                return adjust(head,1);
            }
        }

        if(x < head->key){
            if(removeUtil(head->left, x)) return true;
            return adjust(head,0);
        }
        else {
            if(removeUtil(head->left, x)) return true;
            return adjust(head,1);
        }
    }



    node_avl<T> * searchUtil(node_avl<T> * head, T x){
        if(head == nullptr) return nullptr;
        T k = head->key;
        if(k == x) return head;
        if(k > x) return searchUtil(head->left, x);
        if(k < x) return searchUtil(head->right, x);
    }

public:
    int getHeight(node_avl<T>* temp)  const {
        if (temp == nullptr)	return -1;
        int leftHeight = getHeight(temp->left);
        int rightHeight = getHeight(temp->right);

        if (leftHeight > rightHeight) return leftHeight + 1;
        else return rightHeight + 1;
    }
};
