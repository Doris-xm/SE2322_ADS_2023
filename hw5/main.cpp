#include <iostream>
#include "skipList.h"
#include "rbtree.h"
#include "AVLtree.h"
#include "stdlib.h"
#include <vector>
#include <algorithm>
#include <fstream>

//50,100,2000,5000,10000
const int Size =10000;
vector<int> rand_num;

static inline uint64_t rdtsc()
{
    uint32_t low, high;
    asm volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t)high << 32) | low;
}

void rand_gen() { // 生成测试集
    srand(time(nullptr));
    ofstream outfile1, outfile2;
    outfile1.open("./data/rand_num5.txt");
    outfile2.open("./data/order_num5.txt");
    outfile1 << Size << endl;
    outfile2 << Size << endl;
    for (int i = 0; i < Size; ++i) {
        rand_num.push_back(i);
        outfile2 << i << endl;
    }
    random_shuffle(rand_num.begin(), rand_num.end());
    for(auto it = rand_num.begin();it != rand_num.end();++it)
        outfile1 << (*it) << endl;
//    生成搜索测试集
    for(int i : {16,8,4,2,1}) {
        outfile1 << Size / i << endl;
        outfile2 << Size / i << endl;
        for(int j = 0; j < Size / i;++j) {
            outfile2 << j << endl;
            outfile1 << rand() % Size << endl;
        }
    }

    outfile1.close();
    outfile2.close();
}

void test_rbtree(string filename) {
    uint64_t start, end;
    RedBlackTree rbtree;

    fstream infile(filename, std::ios_base::in);
    if (!infile.is_open()) {
        throw std::runtime_error("ERROR: Failed to open file: " + filename);
    }
    auto &fin = infile;

    int size;

    fin >> size;
    cout<<"Size : "<< size <<endl;
    start = rdtsc();
    for(int i = 0; i < size;++i) {
        int temp;
        fin >> temp;
        rbtree.insert(temp);
    }
    end = rdtsc();
    cout<<"RBtree insert time is "<<end - start<<endl;
    cout<<endl;

    for(int i=0;i < 5; ++ i) {
        int search_num;
        fin >> search_num;
        cout<<"Search num : "<< search_num <<endl;
        start = rdtsc();
        for(int j = 0; j < search_num;++j) {
            int temp;
            fin >> temp;
            rbtree.search(temp);
        }
        end = rdtsc();
        cout<<"RBtree search time is "<<end - start<<endl;
        cout<<"Average search time is "<<(end - start) / search_num<<endl;
        cout<<endl;
//        cout<<search_num<<'\t'<<end - start<<'\t'<<(end - start) / search_num<<endl;
    }

}
void test_avl(string filename) {
    uint64_t start, end;
    AVL<int> avltree;

    ifstream infile(filename, ios::in);
    auto &fin = infile;
    int size;

    fin >> size;
    cout<<"Size : "<< size <<endl;
    start = rdtsc();
    for(int i = 0; i < size;++i) {
        int temp;
        fin >> temp;
        avltree.insert(temp);
    }
    end = rdtsc();
    cout<<"AVL insert time is "<<end - start<<endl;
    cout<<endl;

    for(int i=0;i < 5; ++ i) {
        int search_num;
        fin >> search_num;
        cout<<"Search num : "<< search_num <<endl;
        start = rdtsc();
        for(int j = 0; j < search_num;++j) {
            int temp;
            fin >> temp;
            avltree.search(temp);
        }
        end = rdtsc();
        cout<<"AVL search time is "<<end - start<<endl;
        cout<<"Average search time is "<<(end - start) / search_num<<endl;

//        cout<<search_num<<'\t'<<end - start<<'\t'<<(end - start) / search_num<<endl;
        cout<<endl;
    }

}
void test_skiplist(string filename) {
    uint64_t start, end;
    KVStore skiplist;

    ifstream infile(filename, ios::in);
    auto &fin = infile;

    int size;

    fin >> size;
    cout<<"Size : "<< size <<endl;
    start = rdtsc();
    for(int i = 0; i < size;++i) {
        int temp;
        fin >> temp;
        skiplist.put(temp);
    }
    end = rdtsc();
    cout<<"SkipList insert time is "<<end - start<<endl;
    cout<<endl;

    for(int i=0;i < 5; ++ i) {
        int search_num;
        fin >> search_num;
        cout<<"Search num : "<< search_num <<endl;
        start = rdtsc();
        for(int j = 0; j < search_num;++j) {
            int temp;
            fin >> temp;
            skiplist.get(temp);
        }
        end = rdtsc();
        cout<<"SkipList search time is "<<end - start<<endl;
        cout<<"Average search time is "<<(end - start) / search_num<<endl;
        cout<<endl;

//        cout<<search_num<<'\t'<<end - start<<'\t'<<(end - start) / search_num<<endl;
    }

}

void test_rotate() {
    AVL<int> avltree;
    RedBlackTree rbtree;
    for(int i = 1;i <=5;++i) {
//        string s= "./data/rand_num";
        string s= "./data/order_num";
        s += to_string(i) + ".txt";
        ifstream infile(s, ios::in);
        auto &fin = infile;

        int size;

        fin >> size;
        cout<<"Size : "<< size <<endl;
        for(int i = 0; i < size;++i) {
            int temp;
            fin >> temp;
            avltree.insert(temp);
            rbtree.insert(temp);
        }
        cout<<"AVL rotate num is "<<avltree.rotateCount<<endl;
        cout<<"RBtree rotate num is "<<rbtree.rotateCount<<endl;
        cout<<endl;
//        cout<<avltree.rotateCount<<'\t'<<rbtree.rotateCount<<endl;
    }
}
int main() {
//    rand_gen(); //用于生成测试集
    cout<<"Random case: "<<endl;
    for(int i = 1;i <=5;++i) {
        string s= "./data/rand_num";
        s += to_string(i) + ".txt";
        test_rbtree(s);
        test_avl(s);
        test_skiplist(s);
    }
    cout<<"Order case: "<<endl;
    for(int i = 1;i <=5;++i) {
        string s= "./data/order_num";
        s += to_string(i) + ".txt";
        test_rbtree(s);
        test_avl(s);
        test_skiplist(s);
    }
    test_rotate();
    return 0;
}
