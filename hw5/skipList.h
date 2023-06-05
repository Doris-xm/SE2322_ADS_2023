#pragma once
#include <vector>
#include <string>
#include <list>

using namespace std;

struct node{
    int key;
    int level;
    vector<node*> point_list;
    node(int k = 0, node* n = nullptr,int l = 0):key(k),level(l) {
        point_list.push_back(n);
    }
};


class KVStore {
    // You can add your implementation here
private:
    int Max_level;
    node* head;
    node* tail;
    int P;

public:
    KVStore();

    ~KVStore();

    void put(uint64_t key) ;

    uint64_t get(uint64_t key) ;

    bool del(uint64_t key) ;

    void reset() ;

    void clear(node* &h);

  };
