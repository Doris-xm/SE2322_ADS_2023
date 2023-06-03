#include <iostream>
#include <algorithm>
using namespace std;
#include "SplayTree.h"
#include "AvlTree.h"
#include "ctime"

int n = 1000;
int m = 1000000;
void Test(double percent) {
    srand(time(nullptr));
    int k = percent * n / 100;
    cout<<"Test:: k/n = "<<percent <<"%"<<endl;
    clock_t start, end;

    vector<int> *vec =  new vector<int>;
    for (int i = 0; i < n; ++i) {
        vec->push_back(i);
    }
    random_shuffle(vec->begin(), vec->end());


    int key = rand() % n;//搜索的起始值
    vector<int> *test =  new vector<int>;

    for (int i = 0; i < k; ++i) {
        for(int j = 0; j < m/k ; ++j) {
            test->push_back((i + key) % n);
        }
    }
    random_shuffle(test->begin(), test->end());

    SplayTree<int, int> sTree;  //both key and value are of int type. They can be of any type. They
    // both can be of different type. If key is of nonprimitive type, then <, >, == operators must be overloaded.
    // To ensure that value is always deep copied, assignment operator (=) must be overloaded.

    for(vector<int>::iterator it = vec->begin(); it != vec->end(); it++)
        sTree.insert(*it,*it);

    start = clock();
    for(vector<int>::iterator it = test->begin(); it != test->end(); it++)
        sTree.search(*it);
//    for(int j = 0; j < k; j++){
//        for(int i = 0; i < m / k; i++ )
//            sTree.search((key + j) % n);
//    }
//    for(int i = 0; i < m / k; i++ ) {
//        for(int j = 0; j < k; j++)
//            sTree.search((key + rand() % k) % n);
//    }
    end = clock();

    cout << "Search time of Splay Tree : " <<end - start<< endl;


    AVL<int> AvlTree;
    for(vector<int>::iterator it = vec->begin(); it != vec->end(); it++)
        AvlTree.insert(*it);

    start = clock();
    for(vector<int>::iterator it = test->begin(); it != test->end(); it++)
        AvlTree.search(*it);

//    for(int j = 0; j < k; j++){
//        for(int i = 0; i < m / k; i++ )
//            AvlTree.search((key + j) % n);
//    }
//    for(int i = 0; i < m / k; i++ ) {
//        for(int j = 0; j < k; j++)
//            AvlTree.search((key + rand() % k) % n);
//    }
    end = clock();

    cout << "Search time of AVL Tree : " <<end - start<< endl;

    delete vec;
    delete test;
}

int main()
{
    Test(0.1);
    Test(0.5);
    Test(1);
    Test(3);
    Test(15);
    Test(45);
    Test(70);
    Test(90);


    return 0;
}