#include <algorithm>
#include <iostream>
#include <vector>
#include "ctime"
using namespace std;

template <typename T>
class node{
    public:
        T key;
        int height;
        node * left;
        node * right;
        node(T k){
            height = 1;
            key = k;
            left = NULL;
            right = NULL;
        }
};

template <typename T>
class AVL{
    public:
        node<T> * root;
//        int num;

        AVL(){root = nullptr;}
        void insert(T x){
            insertUtil(root, x);
        }

        void remove(T x){
            root = removeUtil(root, x);
        }

        node<T> * search(T x){
            return searchUtil(root,x);
        }

        void inorder(){
            inorderUtil(root);
            cout << endl;
        }
    private:
        int height(node<T> * head){
            if(head == NULL) return 0;
            return head->height;
        }

        node<T> * rightRotation(node<T> * head){
            node<T> * newhead = head->left;
            head->left = newhead->right;
            newhead->right = head;
            head->height = 1+max(height(head->left), height(head->right));
            newhead->height = 1+max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        node<T> * leftRotation(node<T> * head){
            node<T> * newhead = head->right;
            head->right = newhead->left;
            newhead->left = head;
            head->height = 1+max(height(head->left), height(head->right));
            newhead->height = 1+max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        // Traverse and print AVL tree
        void inorderUtil(node<T> * head){
            if(head==NULL) return ;
            inorderUtil(head->left);
            cout<<head->key<<" ";
            inorderUtil(head->right);
        }

        void insertUtil(node<T> * &head,const T &x){
            // TODO: finish insertUtil
            if(head == nullptr)
                head = new node<T>(x);
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

    bool adjust(node<T> *&t, int subTree) {
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

        bool removeUtil(node<T> * head,const T &x){
            // TODO: finish removeUtil
            if(head == nullptr) return true;
            if(x == head->key) {
                if(!head->left || !head->right) {
                    node<T> *old = head;
                    head = (head->left)? head->left : head->right;
                    delete old;
                    return false;
                }
                else {
                    node<T>* tmp = head->right;
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



        node<T> * searchUtil(node<T> * head, T x){
            if(head == NULL) return NULL;
            T k = head->key;
            if(k == x) return head;
            if(k > x) return searchUtil(head->left, x);
            if(k < x) return searchUtil(head->right, x);
        }

public:
        int getHeight(node<T>* temp)  const {
            if (temp == NULL)	return -1;
            int leftHeight = getHeight(temp->left);
            int rightHeight = getHeight(temp->right);

            if (leftHeight > rightHeight) return leftHeight + 1;
            else return rightHeight + 1;
        }
};



template <typename T>
class BST{
    // TODO: finish BST according to AVL

public:
    node<T> *root;
    BST(){
        root = nullptr;
    }
    ~BST(){
        makeEmpty(root);
    }
    T *find( const T &x )const{
        if (!root) return nullptr;
        node<T> *p = root;
        while(p){
            if(x == p->key) return &(p->key);
            if(x < p->key) p = p->left;
            else p = p->right;
        }
        return nullptr;
    }

    void insert( const T &x ){
        node<T> *p = root;
        if(!root){
            root=new node<T>(x);return;
        }

        while(p){
            if(x == p->key) return;
            if(x < p->key){
                if(!p->left){
                    p->left = new node<T>(x);return;//父子关系
                }
                p = p->left;
            }
            else{
                if(!p->right){
                    p->right = new node<T>(x);return;
                }
                p = p->right;
            }
        }

    }

    void remove( const T &x ){
        remove(x,root);
    }

private:

    void remove( const T &x,node<T> *&t ){
        if(t == nullptr) return;
        if(x< t->key) remove(x, t->left);
        else if(x> t->key) remove(x, t->right);
        else if(t->left && t->right){
            node<T> *tmp = t->right;
            while(tmp->left) tmp = tmp->left;
            t->key = tmp->key;
            remove(t->key,t->right);
        }
        else {
            node<T> *oldNode = t;
            t = (t->left)? t->left : t->right;
            delete oldNode;
        }
    }

    void makeEmpty(node<T> *t){
        if(!t) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

public:
    int getHeight(node<T>* temp)  const {
        if (temp == NULL)	return -1;
        int leftHeight = getHeight(temp->left);
        int rightHeight = getHeight(temp->right);

        if (leftHeight > rightHeight) return leftHeight + 1;
        else return rightHeight + 1;
    }

};


//TEST PART

void rand_gen(int Num,vector<int>* temp) {
    for (int i = 0; i < Num; ++i) {
        temp->push_back(i + 1);
    }
    random_shuffle(temp->begin(), temp->end());

}



void test(int NUM){
    vector<int> *vec = nullptr;
    vec = new vector<int>;
    clock_t start, end;
    rand_gen(NUM,vec);

    cout<<"randomly generate "<<NUM<<" int to test"<<endl;

    AVL<int> avl;
    BST<int> bst;

    //build tree
    start = clock();
    for(vector<int>::iterator it = vec->begin(); it != vec->end(); it++)
        avl.insert(*it);
    end = clock();
    cout<<"AVL:: Time for building trees is "<<end-start<<endl;
    cout<<"AVL:: Height is "<< avl.getHeight(avl.root) <<endl;

    start = clock();
    for(vector<int>::iterator it = vec->begin(); it != vec->end(); it++)
        bst.insert(*it);
    end = clock();
    cout<<"BST:: Time for building trees is "<<end-start<<endl;
    cout<<"BST:: Height is "<< avl.getHeight(bst.root) <<endl;

    int x1[1000];
    for(int i = 0;i < 1000;++i)
        x1[i] = rand()%NUM +1;


    //search
    start = clock();
    for(int i = 0;i < 1000;++i){
        if (!avl.search(x1[i]))
            cout<<"AVL:: Failed to find "<<x1[i]<<endl;
    }
    end = clock();
    cout<<"AVL:: Successfully find 500 keys. Time: "<<end-start<<endl;


    start = clock();
    for(int i = 0;i < 1000;++i){
        if (!bst.find(x1[i]))
            cout<<"BST:: Failed to find "<<x1[i]<<endl;
    }
    end = clock();
    cout<<"BST:: Successfully find 500 keys. Time: "<<end-start<<endl;


    delete vec;
}

int main(){
    cout<<"TEST 1"<<endl;
    test(500);
    cout<<endl;

    cout<<"TEST 2"<<endl;
    test(5000);
    cout<<endl;

    cout<<"TEST 3"<<endl;
    test(50000);
    cout<<endl;


    return 0;
}
