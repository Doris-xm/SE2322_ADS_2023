#pragma once

#include "kvstore_api.h"
#include <vector>
using namespace std;

struct node{
    int key;
    string s;
    int level;
    vector<node*> point_list;
    node(int k = 0,string S = "",node* n = nullptr,int l = 0):key(k),level(l),s(S) {
        point_list.push_back(n);
    }
    ~node(){
        point_list.clear();
    }
};


class KVStore : public KVStoreAPI {
    // You can add your implementation here
private:
    int Max_level;
    node* head;
    node* tail;
    int P;

public:
    KVStore();

    ~KVStore();

    void put(uint64_t key, const std::string &s) override;

    std::string get(uint64_t key) override;

    bool del(uint64_t key) override;

    void reset() override;

    void clear(node* &h);

    void scan(uint64_t key1, uint64_t key2, std::list<std::pair<uint64_t, std::string> > &list) override;
};
